
#include "graph.h"
#include "edge.h"
#include "parser.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>

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
      std::vector<Edge> edges;
      std::map<std::string, std::vector<Edge>> tempMap;
      tempMap.insert({dest, edges});
      adj_list_.insert({source, tempMap});
    }
    adj_list_[source][dest].push_back(toInsert);
  }
}
