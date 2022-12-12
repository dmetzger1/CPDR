#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include <algorithm>

#include "edge.h"
#include "parser.h"
#include <set>

class Graph {

  public:
    Graph(string filename);

    std::map<std::string, std::map<std::string, std::vector<Edge>>> getAdjList() { return adj_list_; }

    void getCoords(string filename);
    double cost(string lat1s, string lon1s, string lat2s, string lon2s);
    std::vector<std::string> BFS(std::string airport1, std::string airport2); //returns the path with least amount of edges between 2 vertices (DOES NOT ACCOUNT FOR STOPS OR ANY WEIGHTS)
    pair<vector<string>, int> dijkstras(string source, string dest, string filename);
    bool IDDFS(std::string src, std::string target, int max_depth);
    bool DFS(std::string src, std::string target, std::set<string>& visited);
    bool DLS(std::string src, std::string target, int limit);

    std::map<std::string, std::pair<std::string, std::string>> coords;
    
    std::set<std::string> airports_;
  private:
    //maps the source id to a map (adjacent list) of dest id and vector of ways to get there
    std::map<std::string, std::map<std::string, std::vector<Edge>>> adj_list_;
};
