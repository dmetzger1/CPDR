# CPDR

Repository for the CS 225 Final Project, which will build data structures from airline flights allow you to traverse the data.

To run main, run "make exec" and "bin/exec" in terminal
## Location of Files/Deliverables

 - Code: All of the code we created for this project is in the "src" folder within our directory.
 - Tests: All of the test cases we created for this project can be found under the "tests" folder under "tests.cc"
 - Data: All the data we used can be found under the "data_" folder
 - Written report: The written report can be found in the main directory under "results.md" 
 - Presentation video: The video can be found at 

## Running Instructions

**To build and run the executable:**

Build with `make exec` and run with `bin/exec "input1.txt" "input2.txt" ` where `"input1.txt"` is the routes file you are inputting and `"input2.txt"` is the airports file you are inputting.
This will prompt you to enter in an airport in the file you submitted for the source, and one for the destination. This then will be output to bin/exec which you can  see the results outputted for each algorithm.

 **To build and run the test suite:**

Build with `make tests` and `bin/tests` to run the test suite 
Tests we have created with descriptions:

 - Testing adjacency list: Tests to ensure that the size of the adjacency list on a few airports is correct to show we are implementing the graph correctly
 - Testing correct edges: Tests that the edge components are correct for a given edge between 2 airports (the parsing finds the correct information)
 - Testing shortest path is correct: Tests BFS using an expected output on a test case file (a smaller dataset)
