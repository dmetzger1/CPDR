#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include "airport.h"
#include "edge.h"
#include "parser.h"

class Graph {

  public:
    Graph();

    std::vector<std::string> airports_;

  private:
    std::map<Airport, std::map<Airport, std::vector<Edge>>> adj_list_;
};