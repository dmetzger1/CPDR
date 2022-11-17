#include <iostream>

#include "functions.hpp"
#include "parser.h"
#include "graph.h"
#include "airport.h"
#include "edge.h"

int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    std::cout << "Howdy, " << argv[i] << std::endl;
  }
  std::cout << Howdy("Rachel") << std::endl;
 //data_list();
 data_structs(); //prints out the first few dataset line and then prints them out as a struct as well
  Graph* g = new Graph();
  std::cout<< g->airports_[0] << std::endl;
}
