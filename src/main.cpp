#include <iostream>

#include "functions.hpp"
#include "parser.h"
#include "graph.h"

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

  Graph * g = new Graph();
  auto testList = g -> getAdjList();
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
  std::cout <<"The amount of airports is " << g -> airports_.size() << std::endl;
  std::cout << "Map size is " << g -> getAdjList().size() << std::endl;
  /*for(auto it = g->airports_.begin(); it != g->airports_.end(); ++it){
    cout<<*it<<endl;
  }*/
  Graph();
  vector<string> test;
  std::string air1 = "THL";
  std::string air2 = "ISP";
  test = g->shortestPath(air1, air2);
  cout<<"and now for the shortest path"<<endl;
  for(unsigned long i = 0; i < test.size(); i++){
    cout<<test[i]<<endl;
  }
  if(test.size() == 0){
    cout<<"there is no path between the airports"<<endl;
  }
}
