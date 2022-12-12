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

    //creates the edge from the source to the destination, along with the number of stops between the two flights.
    Edge toInsert(source, dest, flight_list[i].airline, flight_list[i].num_stops);

    // if we've seen the source before, just add to adjacency list, else create new map entry
    std::set<std::string>::iterator it = airports_.find(source);   

    std::set<std::string>::iterator it2 = airports_.find(dest);    

    //if we've never sen the source or the destination before, we need to add this aiprot to the aiports_ list
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
    //inserts edge into adjacency list
    adj_list_[source][dest].push_back(toInsert);
  }
}

double Graph::cost(string lat1s, string lon1s, string lat2s, string lon2s) {
  double radius = 6371; // radius of earth in KM


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
  //gets structs from the distances data file
  std::vector<Airports> airport_list = aiports_data_structs(filename);
  for (unsigned i = 0; i < airport_list.size(); i++) {
    std::string airport_IATO = airport_list[i].IATA;
    std::string airport_ICAO = airport_list[i].ICAO;

    //checks which version of the aiport ID we have in our airports list
    if (airports_.count(airport_IATO) || airports_.count(airport_ICAO)) {
      
      std::string airport_id = "";
      if (airports_.count(airport_IATO)) {
        airport_id = airport_IATO;
      } else {
        airport_id = airport_ICAO;
      }

      //makes pair of the latitude and latitiude of the specific airport
      pair<string, string> toInsert = make_pair(airport_list[i].latitude, airport_list[i].longitude);
      coords.insert({airport_id, toInsert});
    }
  }
}

std::vector<std::string> Graph::BFS(std::string airport1, std::string airport2) {
  
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

pair<vector<string>, int> Graph::dijkstras(string source, string dest, string filename) {
  pair<vector<string>, int> return_pair;

  if (airports_.find(source) == airports_.end() || airports_.find(dest) == airports_.end()) { // checks if airports are in list of airports
    return_pair.second = -1;
    return return_pair;
  }
  //creates our maps that maintain distances and visited
  map<string, double> distances;
  map<string, bool> visited;

  map<string, string> previous;

  //other than source, all distances need to be the max value (infinity)
  for (string airport : airports_) {
    distances[airport] = INFINITY;
  }

  distances[source] = 0;

  //other than source, mark all other nodes as unvisited
  for (string airport : airports_) {
    visited[airport] = false;
    previous[airport] = "none";
  }

  //initializing our priority que based on the calculated distances
  priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double,string>>> unvisited;
  unvisited.emplace(0, source);

  getCoords(filename); // initializes coords

  while (!unvisited.empty()) {
    auto top = unvisited.top();
    unvisited.pop();

    double distance = top.first;
    string node = top.second;
    

    if (visited[node]) {
      continue;
    }

    visited[node] = true;
    for (const auto& neighbor : adj_list_[node]) {

      //gather coords for neighbor
      string neighbor_node = neighbor.first;
      string lat1s = coords[node].first;
      string lon1s = coords[node].second;
      string lat2s = coords[neighbor_node].first;
      string lon2s = coords[neighbor_node].second;

      //calculate distance between current node and neighbor node
      double neighbor_distance = cost(lat1s, lon1s, lat2s, lon2s);
      double potential_distance = neighbor_distance + distance;

      // if potential distance is smaller than neighbor distance update distance map
      if (potential_distance < distances[neighbor_node])
      {
        distances[neighbor_node] = potential_distance;
        previous[neighbor_node] = node;

       
        
        unvisited.emplace(distances[neighbor_node], neighbor_node);
        
      }
    }
  }
  if(distances[dest] == INFINITY){ //checking to see if the destination was ever reaching
    return_pair.second = 0.0;
    return return_pair;
  }
  //initializing shortest path
  vector<string> path;
  string cur = dest;
  path.push_back(cur);
  //iterate through previous to create path
  while(cur != source){

    path.push_back(previous[cur]);
    cur = previous[cur];
  }
  reverse(path.begin(), path.end());

  
   return_pair.first = path;
   int dist_int = (int) round(distances[dest]);
   return_pair.second = dist_int;

  return return_pair;
}

//randomly generate graphs, randomly select two points on the graph
//check for valid path
//create my csv file that opnly has like 10 cities amnd flights
bool Graph::DLS(std::string src, std::string target, int limit) {
  if (airports_.find(src) == airports_.end() || airports_.find(target) == airports_.end()) { // checks if airports are in list of airports
    return false;
  }
  if (src == target) {
    return true;
  }

  //if we have reached our depth limit and the current element is not what we want, return
  if (limit <= 0) {
    return false;
  }
  
  std::map<std::string, std::vector<Edge>> inner_list = adj_list_[src];

  //goes through neighbors of src
  for (auto i : inner_list) {
    std::string loc = i.first;

    if (DLS(loc, target, limit-1) == true) {
      return true;
    }
  }
  return false;
}


bool Graph::DFS(std::string src, std::string target, std::set<string>& visited) {
  if (airports_.find(src) == airports_.end() || airports_.find(target) == airports_.end()) { // checks if airports are in list of airports
    return false;
  }
  if (src == target) {
    return true;
  }
  visited.insert(src); //inserts src into seen set
  std::map<std::string, std::vector<Edge>> inner_list = adj_list_[src];

  //goes throught the neighbors of source
  for (auto i : inner_list) {
    std::string loc = i.first;
    if (visited.count(loc) == false && DFS(loc, target, visited)) {
      visited.insert(loc);
      return true;
    }
  }
  return false;
}

bool Graph::IDDFS(std::string src, std::string target, int max_depth)
{
  if (airports_.find(src) == airports_.end() || airports_.find(target) == airports_.end()) { // checks if airports are in list of airports
    return false;
  }
  for (int i = 0; i <= max_depth; i++) {
    if (DLS(src, target, i) == true) {
      return true;
    }     
  }
  return false;
}
