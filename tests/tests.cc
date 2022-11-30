#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.h"
#include <string>

#include "functions.hpp"

TEST_CASE("A test case", "[case-1]") {
  bool something = true;
  REQUIRE(something == true);
}

TEST_CASE("A test case", "[case-1]") {
  bool something = true;
  REQUIRE(something == true);
}

//write tests cases for, shortest path, and graph

//graph, verify that the correct number of airports, correct number of unique arilines, the adjacency list is correct


