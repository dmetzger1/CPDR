# CPDR

Repository for the CS 225 Final Project, which will build data structures from airline flights allow you to traverse the data.

To run main, run "make exec" and "bin/exec" in terminal
## Location of Files/Deliverables

 - Code: All of the code we created for this project is in the "src" folder within our directory.
 - Tests: All of the test cases we created for this project can be found under the "tests" folder under "tests.cc"
 - Data: All the data we used can be found under the "data_" folder
 - Written report: The written report can be found in the main directory under "results.md" 
 - Presentation video: The video can be found at [this link](https://youtu.be/IYe8nqEj9VA)

## Running Instructions
Delete the original build, run `mkdir build`, `cd build`, and `cmake ..`, then:

**To build and run the executable:**


Build with `make` and run with `./main "input1.txt" "input2.txt" ` where `"input1.txt"` is the routes file you are inputting and `"input2.txt"` is the airports file you are inputting.
For example, we run ./main ../data_/routes.dat.txt ../data_/airports.dat.txt 
This will prompt you to enter in an airport in the file you submitted for the source, and one for the destination. This then will be outputted which you can  see the results outputted for each algorithm.


 **To build and run the test suite:**

Build with `make` and `./test` to run the test suite 
Tests we have created with descriptions:

 - Testing adjacency list: Tests to ensure that the size of the adjacency list on a few airports is correct to show we are implementing the graph correctly
 - Testing correct edges: Tests that the edge components are correct for a given edge between 2 airports (the parsing finds the correct information)
 - Testing shortest path is correct: Tests BFS using an expected output on a test case file (a smaller dataset)
 - Testing IDDFS: Tests IDDFSS using a source and destination, verifies that runtime is faster than normal DFS and that source and destination are connected.
 - Testing shortest distance is correct: Tests Dijkstra's algorithm using an expected output for both the total shortest distance and path between two airports from a test case (a smaller dataset), as well as a couple from the larger dataset.
