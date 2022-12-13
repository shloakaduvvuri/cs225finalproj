# cs225finalproj

# Installation Instructions

Our project exists in a github repository at https://github.com/shloakaduvvuri/cs225finalproj. Our three algorithms and data parsing exist in the main.cpp file. Our tests exist in the tests folder in this same github repository, in the tests.cpp file. Our written report, presentation video, and presentation slides are in the folder titled Documentation contained in this same github repository. Our dataset is also in this github repository, within the txt file titled roadNet-TX.txt. 
To build and run this project, follow the instructions below: 
Run git clone https://github.com/shloakaduvvuri/cs225finalproj.git in terminal
In the terminal, run make && ./main to see the outputs of the data parsing, BFS traversal, Djikstra’s and Euler Path algorithm. 
If you are interested in changing values, find the lines of code within each algorithm in our main.cpp that hold variables such int source, or int from. If you were to save another node to these values, based on what is in the original dataset, your resulting values would be changed. 
To build and run the tests for this project, follow the instructions below: 
Run git clone https://github.com/shloakaduvvuri/cs225finalproj.git in terminal
In the terminal, run make test && ./test to see the outputs of the tests that we wrote for the data parsing, BFS traversal, Djikstra’s and Euler Path algorithm.
If the make test command is not functional, scroll to the bottom of the main.cpp file, and uncomment the final block of code. These are manual tests that are exactly the same as what we wrote in tests.cpp, but implemented in main.cpp. 


# Project Proposal

## Leading Question 
For this project, we’re going to be researching road networks in Texas. Using a dataset containing information about highways, connections, and cities in Texas, we will create a function to find the shortest path between 2 input cities. We will do this using the breadth-first search method, Djikstra’s algorithm, and the Eulerian path cycle identification algorithm. Our traversal will be covered by BFS, Djikstra’s will cover our in class algorithm, and our uncovered algorithm will be the Eulerian path algorithm. Our dataset contains information about direct connections between nodes. In this case, a node represents a city. Thus, when we are finding the shortest path between two input nodes, we will find the lowest number of edges we must travel through. This general search tool can be used to find the cities one must travel through to efficiently get from one place to the next. BFS will allow us to explore all the nodes available in this dataset, and recognize what paths exist between cities. This traversal will be useful in finding different routes from one city to another. For each algorithm, we will find the shortest path between two cities and return the number of intermediary cities between the start and end. At each node, we will check for the next shortest step towards the destination node. Since the graph is unweighted, the distance between each node will be represented as 1. So, we will find the shortest number of edges, or “steps'' necessary. For finding the best Eulerian path between two cities, we will find the shortest path between 2 cities where no city or edge, or “road” is repeated. This will allow us to compare if the shortest path found in our Djisktra’s algorithm implementation is the same as this most efficient path found in our Eulerian path implementation.

## Dataset Acquisition
Our final project uses an accessible dataset, publicly accessed on the internet, from Stanford University (http://snap.stanford.edu/data/roadNet-TX.html). The dataset shows Texas road networks, where the roads and cities are represented by nodes and edges.

## Data Format
The Texas Road Network dataset information is sourced from Stanford University (http://snap.stanford.edu/data/roadNet-TX.html). The input format of the dataset is a .txt file which we will then convert into a map. The key will be nodes and the value will be a vector of node neighbors. This way, the data can be more easily read and accessed. The data is stored as an integer that lists the ID number of one node and the ID number of the node it connects to. This file is quite large, as it has 1,379,917 nodes and 3,843,320 edges. We plan to use all of the given data because these nodes represent connections. If we remove some of the connections, we might remove some road pathways, which would render our data unusable in some scenarios. 

## Data Correction
The input data is a .txt file which we will parse by using filestream. To check if the input data is error free, we are going to check the map that it creates and test that all the keys have valid values. We can write tests to see if the map is filled in properly, since there will be too many data points to manually check them. If some don’t have a value, we can remove them from the dataset as they would be outliers. There would be no “outlier” points in a traditional sense because cities, represented by nodes here, are very interconnected. Thus, there will always be a path that connects one city/node to the next. If there happens to be a node that does not have any paths to a city, we will delete that point, as it might be a mistake. This dataset is based off of real cities in Texas, thus it does not make sense for any values to not be physically possible.

## Data Storage
The data we are trying to represent involves the mapping of roads in Texas. In order to best represent the destinations and the roads connecting them, we will be using a directed, unweighted graph. By using a directed graph, we will be able to distinguish which way each road allows passengers to travel. We will be using an unweighted graph since we are looking at the roads that connect the various destinations. In order to represent the graph, we will be utilizing a map where the key will represent each destination and the value will be a vector of all the locations the destination is connected to through a single road. We estimate the storage complexity to be O(n) where n is the number of entries in the map.

## Algorithm 
Function Inputs:
We are representing the dataset using an unweighted, directed graph. We are representing the graph using a map, in which the key is an integer, which represents the index of the city, and the value is a vector, which stores the index of the city’s neighboring cities. Djikstra’s algorithm is an algorithm for finding the shortest paths between nodes in a graph, which in our case, represents road networks. We will convert the map connecting one integer node to another integer node into a map connecting each node to a vector of all its neighbors. This will be the data structure we use to represent our graph for all graph algorithms.  For example, if the nodes of the graph represent cities, Dijkstra's algorithm can be used to find the shortest route between one city and all other cities. We will use the output of Djiktra’s algorithm to find the shortest number of intermediary cities, given our inputs which are the indices of 2 cities and the map. An overview of Djikstra’s algorithm is as follows:
        1. Mark all nodes unvisited. Create a set of all the unvisited nodes called the unvisited set.
        2. Assign to every node a tentative distance value.
        3. For the current node, compare the newly calculated tentative distance to the one currently assigned to the neighbor and assign it the smaller one.
        4. When we are done considering all of the unvisited neighbors of the current node, mark the current node as visited and remove it from the unvisited set.
        5. If the destination node has been marked visited, then stop.
        6. Otherwise, select the unvisited node that is marked with the smallest tentative distance, set it as the new current node, and go back to step 3.

Function Outputs:
Given City A and City B as our inputs, we are trying to find the shortest number of intermediary cities that someone must travel through to get from A to B. The output is represented as an integer. We will use the outputs from our given algorithms to find which algorithm provides the most efficient route, whether it was the traversal, Djikstra’s, or Eulerian path. We will take the route that is returned, and find which one travels through the shortest amount of cities, returning an integer to represent that. That will allow us to visualize which path we found was shortest, and act as a comparison between checking the accuracy and general efficiency of each algorithm. This will be printed out to users, allowing them to use this as a search tool to see which path of their options is best for them to take. 

Function Efficiency:
Within our implementation, we will be using Djikstra’s algorithm, Eulerian’s algorithm, and a breadth first search. For Djikstra’s, we will aim for the Big O efficiency for time complexity to be O(N^2) and for memory to be O(N^2) where N will represent the number of nodes in our graph. We will also be utilizing Eulerian’s algorithm for which the time complexity we will aim to be O(N) and for memory we will aim for O(N). The breadth-first search algorithm will take up at most O(N+E) time where N is the number of nodes and E represents the number of edges. 

## Timeline
Data Acquisition, Cleaning, Processing into IDE - November 7th
BFS Algorithm Completion + Tests - November 18th
Dijkstra's Algorithm Completion + Tests - November 30th
Eulerian Path Algorithm Completion + Tests - December 5th
Final Product Testing - December 6th
Presentation Completion + Submission - December 7th
