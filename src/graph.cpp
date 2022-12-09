#include "graph.h"
#include "edge.h"
#include "parser.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <math.h>
#include <cmath>

using namespace std;
Graph::Graph(string filename) {
  std::vector<Flights> flight_list = data_structs(filename); //calls the csv parser to get list of flightts
  for (unsigned i = 0; i < flight_list.size(); i++) {

    //create source and destination airport and edge connecting the two
    std::string source = flight_list[i].source;
    std::string dest = flight_list[i].dest;

    Edge toInsert(source, dest, flight_list[i].airline, flight_list[i].num_stops);

    // if we've seen the source before, just add to adjacency list, else create new map entry
    std::set<std::string>::iterator it = airports_.find(source);   

    std::set<std::string>::iterator it2 = airports_.find(dest);    

    if (it2 == airports_.end()) {
      airports_.insert(dest);
    }

    if (it == airports_.end()) {
      airports_.insert(source);
      airports_.insert(dest);
      std::vector<Edge> edges;
      std::map<std::string, std::vector<Edge>> tempMap;
      tempMap.insert({dest, edges});
      adj_list_.insert({source, tempMap});
    }
    adj_list_[source][dest].push_back(toInsert);
  }
}

double Graph::cost(string lat1s, string lon1s, string lat2s, string lon2s) {
  double radius = 6371; // radius of earth in KM
  std::cout << lat1s << " " << lon1s << " " << lat2s << "  " << lon2s << std::endl;

  std::cout << lat2s << std::endl;

  double lat1 = stod(lat1s);
  double lon1 = stod(lon1s);
  double lat2 = stod(lat2s);
  double lon2 = stod(lon2s);

  double deg_lat = lat2 - lat1;
  double deg_lon = lon2 - lon1;
  double rad_lat = deg_lat * (M_PI/180); // does pi work
  double rad_lon = deg_lon * (M_PI/180);
  
  double a = sin(rad_lat/2) * sin(rad_lat/2) + cos(lat1 * (M_PI/180)) * cos(lat2 * (M_PI/180)) * sin(rad_lon/2) * sin(rad_lon/2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  double d = radius * c;
  return d;
}

void Graph::getCoords(string filename) {
  std::vector<Airports> airport_list = aiports_data_structs(filename);
  for (unsigned i = 0; i < airport_list.size(); i++) {
    std::string airport_IATO = airport_list[i].IATA;
    std::string airport_ICAO = airport_list[i].ICAO;

    if (airports_.count(airport_IATO) || airports_.count(airport_ICAO)) {
      
      std::string airport_id = "";
      if (airports_.count(airport_IATO)) {
        airport_id = airport_IATO;
      } else {
        airport_id = airport_ICAO;
      }

      pair<string, string> toInsert = make_pair(airport_list[i].latitude, airport_list[i].longitude);
      coords.insert({airport_id, toInsert});
    }
  }
}

std::vector<std::string> Graph::shortestPath(std::string airport1, std::string airport2) {
  cout<<"inside shortest path"<<endl;
  std::vector<std::string> to_return; 
  if (airports_.find(airport1) == airports_.end() || airports_.find(airport2) == airports_.end()) { // checks if airports are in list of airports
    return to_return;
  }
  queue<string> q;
  map<string, bool> visited;
  visited[airport1] = true;
  q.push(airport1);

  map<string, int> depths; // keeping track of distances from airport 1
  map<string, string> prev;
  bool contains_airport_2 = false; //checks if there is a path to airport 2 (in same connected component)

  depths[airport1] = 0;

  while (!q.empty()) {
    string v = q.front();
    q.pop();
    for (std::pair<std::string, std::vector<Edge>> dest_edge_pair : adj_list_[v]) { //for each neighbor
      if (!visited[dest_edge_pair.first]) {
        visited[dest_edge_pair.first] = true;
        q.push(dest_edge_pair.first);
        prev[dest_edge_pair.first] = v;
        depths[dest_edge_pair.first] = depths[v] + 1; 
      }
      if (dest_edge_pair.first == airport2) {
        contains_airport_2 = true;
      } 
    }
  }
  if (contains_airport_2 == false) { // in different connected components
    return to_return;
  }
  //int shortest_path = depths[airport2]; // if we need this in future, returns least amount of edges
  string curr = airport2;
  while (curr != airport1) { // goes back thru path it took to get to airport 2
    to_return.push_back(curr);
    curr = prev[curr];
  }
  to_return.push_back(airport1);
  reverse(to_return.begin(), to_return.end()); // reverses path so airport 1 is the start (in order of start to end)
  return to_return;
}

double Graph::dijkstras(string source, string dest, string filename) {

  cout<<"inside of dijkstras"<<endl;

  map<string, double> distances;
  map<string, bool> visited;

  for (string airport : airports_) {
    distances[airport] = INFINITY;
  }

  distances[source] = 0;

  for (string airport : airports_) {
    visited[airport] = false;
  }

  priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double,string>>> unvisited;
  unvisited.emplace(0, source);

  getCoords(filename); // initializes coords

  while (!unvisited.empty()) {
    cout<<"inside of while loop"<<endl;
    auto top = unvisited.top();
    unvisited.pop();

    string node = top.second;
    double distance = top.first;

    if (visited[node]) {
      continue;
    }
    visited[node] = true;
    for (const auto& neighbor : adj_list_[node]) {

      cout<<"inside of for loop"<<endl;

      string neighbor_node = neighbor.first;
      string lat1s = coords[node].first;
      string lon1s = coords[node].second;
      string lat2s = coords[neighbor_node].first;
      string lon2s = coords[neighbor_node].second;


      std::cout << node << std::endl;
      std::cout << neighbor_node << std::endl;
      double neighbor_distance = cost(lat1s, lon1s, lat2s, lon2s);
      std::cout << "BOYYYY" << std::endl;
      double potential_distance = neighbor_distance + distance;

      if (potential_distance < distances[neighbor_node])
      {
        distances[neighbor_node] = potential_distance;

        cout<<distances[neighbor_node]<<endl;
        
        unvisited.emplace(distances[neighbor_node], neighbor_node);
        if (neighbor_node == dest) {
          cout<<"made it to dest!!!"<<endl;
        }
      }
    }
  }
  cout << "the shortest distance is" << distances[dest] << endl;
  return distances[dest];
}

bool Graph::DLS(std::string src, std::string target, int limit) {
  if (src == target) {
    return true;
  }
   
  if (limit <= 0) {
    return false;
  }
  
  std::map<std::string, std::vector<Edge>> inner_list = adj_list_[src];
  for (auto i : inner_list) {
    std::string loc = i.first;
    if (DLS(loc, target, limit-1) == true) {
      return true;
    }
  }
  return false;
}

bool Graph::DFS(std::string src, std::string target) {
  if (src == target) {
    return true;
  }
  std::map<std::string, std::vector<Edge>> inner_list = adj_list_[src];
  for (auto i : inner_list) {
    std::string loc = i.first;
    if (DFS(loc, target)) {
      return true;
    }
  }
  return false;
}

bool Graph::IDDFS(std::string src, std::string target, int max_depth)
{
    for (int i = 0; i <= max_depth; i++)
    if (DLS(src, target, i) == true)
          return true;
   
    return false;
}
