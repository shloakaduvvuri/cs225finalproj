#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include <catch2/catch_test_macros.hpp>
// #include "src/bfs.cpp"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

map<int, vector<int>> makeMap() {
    int index = 0;
    int key;
    int x;
    ifstream inFile;
    inFile.open("roadNet-TX.txt");
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1);
    }
    map<int, vector<int>> graph_;
    while (inFile >> x) {
        if (index % 2 == 0) {
            key = x;
            if (graph_.find(key) == graph_.end()) {
                vector<int> vals;
                graph_.insert(make_pair(key, vals));
            }
        } else if (index % 2 == 1) {
          graph_[key].push_back(x);  
            
        }
        index++;
    }
    inFile.close();

    for (auto node_relation : graph_) {
        sort(node_relation.second.begin(), node_relation.second.end());
    } 
    return graph_;
}

// TEST_CASE("graph", "check_structure") {
//     //pulled from dataset info
//     map<int, vector<int>> graph_ = makeMap();
//     //unsigned actual_num_nodes = 1379917;
//     int actual_num_edges = 1921660;
//     int undirected_edges = actual_num_edges*2;
//     //REQUIRE(graph_.size() == actual_num_nodes);
//     /* the number of edges represents the total number
//     of connections across all the nodes 
//     (total num of elements in all values vectors)
//     */
//    int count = 0;
//     for (auto node_neighbors : graph_) {
//         count+=node_neighbors.second.size();
//     }
//     REQUIRE(count == undirected_edges);
// }
//153380, 1
// TEST_CASE("graph2", "check_accuracy") {
//     //pulled from dataset info 
//     map<int, vector<int>> graph_ = makeMap();
//     vector<int> neighbors_of_1;
//     for (auto c : graph_.at(1)) {
//         neighbors_of_1.push_back(c);
//     }
//     vector<int> correct_1 = {0, 23, 32};
//     REQUIRE(neighbors_of_1 == correct_1);

//     vector<int> neighbors_of_153380;
//     for (auto c : graph_.at(153380)) {
//         neighbors_of_1.push_back(c);
//     }
//     vector<int> correct_153380 = {153379, 153381, 153382, 153385};
//     REQUIRE(neighbors_of_153380 == correct_153380);
// }
//153408, 153376
// TEST_CASE("graph3", "check_undirected") {
//     //pulled from dataset info 
//     map<int, vector<int>> graph_ = makeMap();
//     int neighbor_of_153408 = 153376;
//     vector<int> to_search = graph_.at(neighbor_of_153408);
//     REQUIRE(find(to_search.begin(), to_search.end(), 153408) != to_search.end());
// }

// TEST_CASE("bfs", "bfs_basic_map") {
//   // replace this section with makeMap() to create actual graph
//   vector<int> tmp;
//   tmp.push_back(2);
//   tmp.push_back(3);
//   tmp.push_back(4);
//   map<int, vector<int>> graph_;
//   graph_.insert({1,tmp});

//   REQUIRE(travelNode(1, 2) == 1);
// }
