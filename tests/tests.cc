#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.h"
#include <string>

#include "functions.hpp"
#include "/Users/patrickcunningham/Programming/CPDR/src/parser.h"
#include "/Users/patrickcunningham/Programming/CPDR/src/graph.h"
#include "/Users/patrickcunningham/Programming/CPDR/src/edge.h"

TEST_CASE("A test case", "[case-1]") {
  bool something = true;
  REQUIRE(something == true);
}

TEST_CASE("Testing adjacency list", "[case-1]") {
  Graph * g = new Graph("/Users/patrickcunningham/Programming/CPDR/data_/test_cases_1.txt");
  std::map<std::string, std::map<std::string, std::vector<Edge>>> adjList = g->getAdjList();

  //tests each airport connects to the correct number of airports
  REQUIRE(adjList["BAL"].size() == 5);
  REQUIRE(adjList["CLE"].size() == 1);
  REQUIRE(adjList["LV"].size() == 0);

  //tests airports don't connect to wrong airports
  REQUIRE(adjList["BAL"].count("SD") == 0);
  REQUIRE(adjList["BAL"].count("CHI") != 0);
}

TEST_CASE("Testing edges are correct", "[case-1]") {
  Graph * g = new Graph("/Users/patrickcunningham/Programming/CPDR/data_/test_cases_1.txt");
  std::map<std::string, std::map<std::string, std::vector<Edge>>> adjList = g->getAdjList();
  REQUIRE(adjList["BAL"]["CHI"][0].airline == "2B");
  REQUIRE(adjList["DAL"]["AUS"][0].source == "DAL");
  REQUIRE(adjList["DAL"]["AUS"][0].dest == "AUS");
  REQUIRE(adjList["SF"]["SD"][0].num_stops == "0");
}

//write tests cases for, shortest path, and graph

//graph, verify that the correct number of airports, correct number of unique arilines, the adjacency list is correct


