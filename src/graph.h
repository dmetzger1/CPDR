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

    /**
     * Initializes the graph. The functions works by moving through the flight list that is generated from our parser function,
     * then extracting the source, destination, airline, and number of stops from the flight. 
     *
     * @param filename The location to the airports dataset
     * @return void - initializes the graph adjacency list
    */
    Graph(string filename);

    std::map<std::string, std::map<std::string, std::vector<Edge>>> getAdjList() { return adj_list_; }

    /**
     * Helper function that initializes the coords map by taking the latitude and longitude of each airport in the graph
     *
     * @param filename The location to the routes dataset
     * @return void - maps each airport id to a pair(latitude, longtitude)
    */
    void getCoords(string filename);
    pair<vector<string>, int> dijkstras(string source, string dest, string filename);
    double cost(string lat1s, string lon1s, string lat2s, string lon2s);

    /**
     * BFS function. Determines both that a path exists between two airports, as well as the shortest path 
     * (in terms of connections) between the two airports
     *
     * @param airport1 The source airport
     * @param airport2 The destination airport
     * @return A vector containing the airport ids of the  shortest path (in terms of connections) between airport1 and airport2. 
     *          Will return an empty vector if no path is found 
     */

    std::vector<std::string> BFS(std::string airport1, std::string airport2); //returns the path with least amount of edges between 2 vertices (DOES NOT ACCOUNT FOR STOPS OR ANY WEIGHTS)

    /**
     * IDDFS Function. 
     * One of the main funcitons to implement. Acts as an evolution onto DFS, allowing it to run more safe as well as faster
     * By providing a depth limit, we force the search algorithm to stop running after a certain depth is reaches. This helps the 
     * algorithm avoid getting lost in a search, as well as finding targets quicker in situations where they are close by.
     *
     * @return bool - returns true if there is a connection between airports, false otherwise
     */

    
    bool IDDFS(std::string src, std::string target, int max_depth);

    /**
     * Helper function that is used to test the effectiveness of IDDFS.
     * 
     * Basic depth first search algorithm, with the goal of it to show how the DFS algorithm has a tendency to get 
     * lost when we do not put a limit on the function - which is a problem that our IDDFS algorithm ultimately solves. 
     *
     * @param source The source airport
     * @param target The destination airport
     * @return bool - returns true if there is a connection between airports, false otherwise
    */

    bool DFS(std::string src, std::string target, std::set<string>& visited);

    /**
     * Helper function that is used to alongside IDDFS. DFS algorithm that includes the depth that the search is currently at
     * 
     *
     * @param source The source airport
     * @param target The destination airport
     * @param limit The current limit that the search is on (is decremented with each iteration) - will stop when limit = 0
     * @return bool - returns true if there is a connection between airports, false otherwise
    */
    bool DLS(std::string src, std::string target, int limit);

    std::map<std::string, std::pair<std::string, std::string>> coords;
    
    std::set<std::string> airports_;
  private:
    /**
    * The storage for the graph. Maps an airport id to an inner map
    * 
    * Inner map contains a mapping between the destination airport to a vector of all the edges that connect the two airports
    * We chose this implementation to demonstrate the fact that there are many ways to reach an airport
    * from another depending on which airline you chose to take.
    */
    std::map<std::string, std::map<std::string, std::vector<Edge>>> adj_list_;
};
