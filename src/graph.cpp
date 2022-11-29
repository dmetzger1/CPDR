#include "graph.h"
#include "edge.h"
#include "parser.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>

using namespace std;
Graph::Graph() {
  std::vector<Flights> flight_list = data_structs(); //calls the csv parser to get list of flightts
  for (unsigned i = 0; i < flight_list.size(); i++) {

    //create source and destination airport and edge connecting the two
    std::string source = flight_list[i].source;
    std::string dest = flight_list[i].dest;

    Edge toInsert(source, dest, flight_list[i].airline, flight_list[i].num_stops);

    // if we've seen the source before, just add to adjacency list, else create new map entry
    std::set<std::string>::iterator it = airports_.find(source);    
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



//randomly generate graphs, randomly select two points on the graph
//check for valid path
//create my csv file that opnly has like 10 cities amnd flights
