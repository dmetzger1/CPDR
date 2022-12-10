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

  Graph * g = new Graph("data_/routes.dat.txt");
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


  g->getCoords("data_/airports.dat.txt");
  std::cout << g->coords.size() << " these are the coord size"<<std::endl;
  std::cout << g->airports_.size() << " these are the list size"<<std::endl;

  string lat1s = g->coords["POL"].first;
  string lon1s = g->coords["POL"].second;
  string lat2s = g->coords["NBO"].first;
  string lon2s = g->coords["NBO"].second;
  string lat3s = g->coords["BOM"].first;
  string lon3s = g->coords["BOM"].second;
  string lat4s = g->coords["CCU"].first;
  string lon4s = g->coords["CCU"].second;
  string lat5s = g->coords["KMG"].first;
  string lon5s = g->coords["KMG"].second;
  string lat6s = g->coords["SYM"].first;
  string lon6s = g->coords["SYM"].second;

  //std::cout << g->coords["BVS"].first << std::endl;

  double c1 = g->cost(lat1s, lon1s, lat2s, lon2s);
  double c2 = g->cost(lat2s, lon2s, lat3s, lon3s);
  double c3 = g->cost(lat3s, lon3s, lat4s, lon4s);
  double c4 = g->cost(lat4s, lon4s, lat5s, lon5s);
  double c5 = g->cost(lat5s, lon5s, lat6s, lon6s);
  double c = c1 + c2 + c3 + c4 + c5;


  double distance_ = g->dijkstras("POL", "SYM", "data_/airports.dat.txt");
  cout<<"the shortest distance between the airports is "<<distance_<<endl;

  cout << "total cost: " << c << endl;

  
}
