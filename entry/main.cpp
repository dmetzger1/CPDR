#include <iostream>

#include "parser.h"
#include "graph.h"
#include <algorithm>

#include "edge.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
        // Print an error message if no input file was specified
        std::cerr << "Error: no input file specified" << std::endl;
        return 1;
    }
  

  Graph * g = new Graph(argv[1]);
  string input1;
  cout << "Enter source airport:";
  cin >> input1;
  string input2;
  cout << "Enter destination airport:";
  cin >> input2;
  vector<string> path = g->BFS(input1, input2);
  if(path.empty()){
    cout<<"There is no path between the airports with BFS"<<endl;
  } else{
    cout << "The path with the least amount of stops from " << input1 << " to " << input2 << " using BFS is " << endl;
    for (string airport : path) {
          cout << airport << endl;
    }
  }

  pair<vector<string>, int> test_d = g->dijkstras(input1, input2, argv[2]);
  cout<<"The shortest distance between the airports using Dijkstra's algorithm is "<<test_d.second<<endl;
  if(test_d.first.empty()){
    cout<<"There is no path between the airports with Dijkstras"<<endl;
  } else{
    cout<<"The shortest distance path between the aiports using Dijkstra's is "<<endl;
    for(unsigned x = 0; x < test_d.first.size(); x++){
      cout<<test_d.first[x]<<endl;
    }
  }

  std::set<string> visited;
  const clock_t begin_time = clock();
  g->DFS(input1, input2, visited);
  float dfs_time = float(clock() - begin_time) * 10000 / CLOCKS_PER_SEC;

  const clock_t begin_time2 = clock();
  g->IDDFS(input1, input2, 3);
  float iddfs_time = float(clock() - begin_time2) * 10000 / CLOCKS_PER_SEC;

  std::cout << "It took DFS " << dfs_time << " seconds to find source while IDFS only took " << iddfs_time << " seconds." << std::endl;


  
}
