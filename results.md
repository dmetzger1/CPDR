# Written Report
**Conor Cunningham, Patrick Cunningham, Danny Metzger, Rachel Samojedny**
## Output and Correctness of Each Algorithm
**BFS:**
For BFS, we first check to make sure the airports are in the file. We then initialize a queue and map to keep track of visited airports. We mark the source airport as visited and push it to the queue. We also keep track of the depths and previous to help create the path at the end.  Entering the "while" loop of the traversal, we traverse until the queue is empty. We pop the front element of the queue and push all unvisited neighbors to the queue and set their previous value and depth value accordingly. We also have a bool check to ensure that there is a path from airport 1 to airport 2 i.e. in the same connected component. We last then go back through the path backwards and then reverse the vector to return a vector that gives the shortest path in terms of least amount of stops i.e. returns those stops. 

The tests we used to ensure our BFS traversal was correct was creating a smaller scale of the test file and finding the expected and ensuring our code matched the expected.
**Dijkstra's:**
For Dijkstra's algorithm, we keep track of the distances at each node, whether each node is visited, and each previous node using maps. We first initialize the distances for every airport to be INFINITY, but 0 at the source.  We then use the standard library priority queue where it compares a double, string pair which contains the distance as the double and the airport as the string, this way, it is ordered by distance ascending. This will be "unvisited". We push our source with a distance of 0 to this queue. We then traverse until this queue is empty and pop the top element, which will  always be the airport with the smallest distance. This first checks to make sure it is not visited. If not, we set it to visited and go through each neighbor of this node and calculate the cost using a cost function we created. This cost function uses latitude and longitude that we set for each airport using a coordinate system. If the cost + current distance < distances[neighbor], then we set the new distances[neighbor] to be cost + current distance and set the previous as well as push it to the queue. Once we leave the traversal, we do a similar backtracking through the previous map to print out the path and then return the shortest distance in km from the source to destination airport.
**Iterative Deepening:**
## The Answer to our Question


