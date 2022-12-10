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

TEST_CASE("Testing shortest path is correct", "[case-1]"){
  Graph * g = new Graph("/Users/patrickcunningham/Programming/CPDR/data_/test_cases_1.txt");
  std::vector<std::string> test1{ "BAL", "DAL", "AUS", "SF", "SD" };
  std::vector<std::string> test2{ "DAL", "BAL", "NY" };
  vector<string> test3;
  REQUIRE(g->BFS("BAL", "SD") == test1);
  REQUIRE(g->BFS("DAL", "NY") == test2);
  REQUIRE(g->BFS("BAL", "LV") == test3);
  REQUIRE(g->BFS("AUS", "SEA") == test3);

}

//graph, verify that the correct number of airports, correct number of unique arilines, the adjacency list is correct

TEST_CASE("Shortest path test2", "[case-1]"){
  Graph * g = new Graph("/Users/patrickcunningham/Programming/CPDR/data_/test_cases_1.txt");
  REQUIRE(g->airports_.size() == 14);
  REQUIRE(g -> getAdjList().size() == 11);
}

TEST_CASE("Testing IDS", "[case-1]"){
  Graph * g = new Graph("/Users/patrickcunningham/Programming/CPDR/data_/test_cases_1.txt");
  REQUIRE(g->IDDFS("BAL", "SF", 10) == true); // distance from BAL to SF is at most ten steps away
  REQUIRE(g->IDDFS("BAL", "SF", 1) == false); //distance from BAL to SF is greater than one
  REQUIRE(g->IDDFS("BAL", "SEA", 1) == true);


  Graph * g2 = new Graph("/Users/patrickcunningham/Programming/CPDR/data_/routes.dat.txt");

  std::set<string> visited;

  const clock_t begin_time = clock();
  REQUIRE(g2->DFS("JER", "GCI", visited) == true);
  float dfs_time = float(clock() - begin_time) * 10000 / CLOCKS_PER_SEC;

  const clock_t begin_time2 = clock();
  REQUIRE(g2->IDDFS("JER", "GCI", 30) == true);
  float iddfs_time = float(clock() - begin_time2) * 10000 / CLOCKS_PER_SEC;

  std::cout << "IT TOOK DFS " << dfs_time << " SECONDS TO FIND THE SOURCE AND ONLY TOOK IDFS " << iddfs_time << " SECONDS TO FIND THE SOURCE" << std::endl;

  REQUIRE(dfs_time > iddfs_time); //shows that IDFS is much faster than DFS when the data set is large

}
