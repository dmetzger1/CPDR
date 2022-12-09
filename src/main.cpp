#include <iostream>

#include "functions.hpp"
#include "parser.h"
#include "graph.h"
#include <algorithm>

#include "edge.h"

int main(int argc, char* argv[]) {
  char* a = argv[0];
  for (int i = 1; i < argc; ++i) {
    //std::cout << "Howdy, " << argv[i] << std::endl;
    a += 'c';
  }
  std::cout << a << std::endl;
  //std::cout << Howdy("Rachel") << std::endl;
  // data_list(); 
  // data_structs(); //prints out the first few dataset line and then prints them out as a struct as well

  Graph * g = new Graph("/Users/patrickcunningham/Programming/CPDR/data_/routes.dat.txt");
  auto testList = g -> getAdjList();

  // cout<< "The adjancency list of AUX is "<< testList["AUX"].size()<<endl;
  // auto testMap = testList.at("4029");
  // std::cout << "Lets look at 4029's adjacency list" << std::endl;
  // for (auto i = testMap.begin(); i != testMap.end(); i++) {
  //   std::cout << "The destination of the flight is " << i->first << std::endl;
  //   std::vector<Edge> edges = i -> second;
  //   for (Edge e : edges) {
  //     std::cout << "The flight traveled from " << e.source << std::endl;
  //     std::cout << "The flight traveled to " << e.dest << std::endl;
  //     std::cout << "The flight traveled through " << e.airline << std::endl;
  //     std::cout << "The flight took " << e.num_stops << " stops" << std::endl;
  //     std::cout << "NEXT FLIGHT" << std::endl;
  //   }
  // }
  // std::cout <<"The amount of airports is " << g -> airports_.size() << std::endl;
  // std::cout << "Map size is " << g -> getAdjList().size() << std::endl;

  // std::vector<std::string> testBFS = g->shortestPath("ZAM", "EFL");
  // for(unsigned i = 0; i < testBFS.size(); i++){
  //   cout<<testBFS[i]<<endl;
  // }


  g->getCoords("/Users/patrickcunningham/Programming/CPDR/data_/airports.dat.txt");
  std::cout << g->coords.size() << " these are the coord size"<<std::endl;
  std::cout << g->airports_.size() << " these are the list size"<<std::endl;

  string lat1s = g->coords["AUX"].first;
  string lon1s = g->coords["AUX"].second;
  string lat2s = g->coords["MAB"].first;
  string lon2s = g->coords["MAB"].second;

  std::cout << g->coords["BVS"].first << std::endl;

  double c = g->cost(lat1s, lon1s, lat2s, lon2s);


  cout << "cost " << c << endl;


  double distance_ = g->dijkstras("AUX", "MAB", "/Users/patrickcunningham/Programming/CPDR/data_/airports.dat.txt");
  cout<<"the shortest distance between the airports is "<<distance_<<endl;
  
}
