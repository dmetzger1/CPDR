
#include "graph.h"
#include "airport.h"
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

    Airport source(flight_list[i].source, flight_list[i].source_id); 
    Airport destination(flight_list[i].dest, flight_list[i].dest_id); 
    Edge toInsert(source, destination, flight_list[i].airline, flight_list[i].num_stops);

    // if we've seen the source before, just add to adjacency list, else create new map entry
    if (std::find(airports_.begin(), airports_.end(), flight_list[i].source) == airports_.end()) {
      airports_.push_back(flight_list[i].airline);
      std::vector<Edge> edges;
      std::map<Airport, std::vector<Edge>> tempMap;
      tempMap.insert({destination, edges});
      adj_list_.insert({source, tempMap});
    }
    adj_list_[source][destination].push_back(toInsert);
  }
}
