#include <catch2/catch_test_macros.hpp>

#include <string>
#include "../src/parser.h"
#include "../src/graph.h"
#include "../src/edge.h"

TEST_CASE("Testing adjacency list", "[case-1]") {
  Graph * g = new Graph("../data_/test_cases_1.txt");
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
  Graph * g = new Graph("../data_/test_cases_1.txt");
  std::map<std::string, std::map<std::string, std::vector<Edge>>> adjList = g->getAdjList();
  REQUIRE(adjList["BAL"]["CHI"][0].airline == "2B");
  REQUIRE(adjList["DAL"]["AUS"][0].source == "DAL");
  REQUIRE(adjList["DAL"]["AUS"][0].dest == "AUS");
}

//write tests cases for, shortest path, and graph

TEST_CASE("Testing shortest path is correct", "[case-1]"){
  Graph * g = new Graph("../data_/test_cases_1.txt");
  std::vector<std::string> test1{ "BAL", "DAL", "AUS", "BUF", "SD" };
  std::vector<std::string> test2{ "DAL", "BAL", "NY" };
  vector<string> test3;
  REQUIRE(g->BFS("BAL", "SD") == test1);
  REQUIRE(g->BFS("DAL", "NY") == test2);
  REQUIRE(g->BFS("BAL", "LAV") == test3);
  REQUIRE(g->BFS("NY", "CLT") == test3);

}

//graph, verify that the correct number of airports, correct number of unique arilines, the adjacency list is correct

TEST_CASE("Shortest path test2", "[case-1]"){
  Graph * g = new Graph("../data_/test_cases_1.txt");
  REQUIRE(g->airports_.size() == 18);
  REQUIRE(g -> getAdjList().size() == 16);
}

TEST_CASE("Testing IDS", "[case-1]"){
  Graph * g = new Graph("../data_/test_cases_1.txt");
  REQUIRE(g->IDDFS("BAL", "SF", 10) == true); // distance from BAL to SF is at most ten steps away
  REQUIRE(g->IDDFS("BAL", "SF", 1) == false); //distance from BAL to SF is greater than one
  REQUIRE(g->IDDFS("BAL", "SEA", 1) == true);


  Graph * g2 = new Graph("../data_/routes.dat.txt");

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

TEST_CASE("Testing shortest distance is correct", "[case-1]"){
  Graph * g = new Graph("../data_/test_cases_1.txt");
  std::vector<std::string> test1{ "BAL", "CHI", "CLE", "SF", "ALB", "SD" };
  std::vector<std::string> test2{ "TMP", "CLT", "DAL", "BAL", "NY"};
  vector<string> test3;
  REQUIRE(g->dijkstras("BAL", "SD", "../data_/test_data_2.txt").first == test1);
  REQUIRE(g->dijkstras("TMP", "NY", "../data_/test_data_2.txt").first == test2);
  REQUIRE(g->dijkstras("BAL", "LAV", "../data_/test_data_2.txt").first == test3);
  REQUIRE(g->dijkstras("NY", "BUF", "../data_/test_data_2.txt").first == test3);
  //checks for the correct paths above

  //checks for the correct distances below 

  REQUIRE(g->dijkstras("BAL", "SD", "../data_/test_data_2.txt").second == 7579);
  REQUIRE(g->dijkstras("TMP", "NY", "../data_/test_data_2.txt").second == 4527);
  REQUIRE(g->dijkstras("BAL", "LAV", "../data_/test_data_2.txt").second == 0.0);
  REQUIRE(g->dijkstras("NY", "BUF", "../data_/test_data_2.txt").second == 0.0); //if two airports are not connected the distance should be 0

  Graph * k = new Graph("../data_/routes.dat.txt"); //testing paths on the larger dataset

  std::vector<std::string> test4{ "APL", "JNB", "MUC", "TRS"};
  std::vector<std::string> test5{"APL", "NBO", "CAI", "ATH", "TIA", "BRI", "TRS" };
  REQUIRE(k->BFS("APL", "TRS") == test4);
  REQUIRE(k->dijkstras("APL", "TRS", "../data_/airports.dat.txt").first == test5);
}

