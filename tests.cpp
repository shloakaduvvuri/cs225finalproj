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
#include <set>
#include <queue>

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

set<int> bfs(map<int, vector<int>> graph_, int from) {
    queue<int> q; 
    set<int> visited;
    q.push(from);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        vector<int> tovisit = graph_.at(curr);
        for (auto i : tovisit) {
            if (visited.find(i) == visited.end()) {
                q.push(i);
                visited.insert(i);
            }
        }
    }
    return visited;
}

vector<pair<int,int>> djikstras(map<int, vector<int>> graph_, int source) {
    int count = 0; 
    vector<pair<int, int>> distances;
    set<int> already_seen;
    distances.push_back(make_pair(source, count));
    queue<int> next_node;
    next_node.push(source);
    already_seen.insert(source);
    while (!next_node.empty() && distances.size() <= 100) {
        int curr = next_node.front();
        next_node.pop();
        vector<int> neighbors = graph_.at(curr);
        count++; 
        for (auto neighbor : neighbors) {
            if (already_seen.find(neighbor) == already_seen.end()) {
                already_seen.insert(neighbor);
                distances.push_back({neighbor, count});
                next_node.push(neighbor);
            }
        }
    }
    sort(distances.begin(), distances.end());
    return distances;
}

map<int, vector<int>> graph_ = makeMap();

TEST_CASE("graph", "check_structure") {
    //unsigned actual_num_nodes = 1379917;
    int actual_num_edges = 1921660;
    int undirected_edges = actual_num_edges*2;
    //REQUIRE(graph_.size() == actual_num_nodes);
    /* the number of edges represents the total number
    of connections across all the nodes 
    (total num of elements in all values vectors)
    */
   int count = 0;
    for (auto node_neighbors : graph_) {
        count+=node_neighbors.second.size();
    }
    REQUIRE(count == undirected_edges);
}
// 153380, 1
TEST_CASE("graph2", "check_accuracy") {
    //pulled from dataset info 
    vector<int> neighbors_of_1;
    for (auto c : graph_.at(1)) {
        neighbors_of_1.push_back(c);
    }
    vector<int> correct_1 = {0, 23, 32};
    REQUIRE(neighbors_of_1 == correct_1);

    vector<int> neighbors_of_153380;
    for (auto c : graph_.at(153380)) {
        neighbors_of_1.push_back(c);
    }
    vector<int> correct_153380 = {153379, 153381, 153382, 153385};
    REQUIRE(neighbors_of_153380 == correct_153380);
}
//153408, 153376
TEST_CASE("graph3", "check_undirected") {
    //pulled from dataset info 
    int neighbor_of_153408 = 153376;
    vector<int> to_search = graph_.at(neighbor_of_153408);
    REQUIRE(find(to_search.begin(), to_search.end(), 153408) != to_search.end());
}

TEST_CASE("djikstra1", "check_source_0") {
    vector<pair<int, int>> result = djikstras(graph_, 0); 
    REQUIRE(result[0].second == 0);
    REQUIRE(result[1].second == 1);
     REQUIRE(result[2].second == 1);
}

TEST_CASE("djikstra2", "check_middle") {
    vector<pair<int, int>> result = djikstras(graph_, 0); 
    REQUIRE(result[4].second == 70);
    REQUIRE(result[6].second == 76);
     REQUIRE(result[27].second == 13);
}

TEST_CASE("bfs1", "check_immediate_neighbor_0") {
    set<int> result = bfs(graph_, 0);
    REQUIRE(result.find(1) != result.end());
}

TEST_CASE("bfs1", "check_immediate_neighbor_0") {
    set<int> result = bfs(graph_, 0);
    REQUIRE(result.find(1) != result.end());
    int count = 0;
    int check = -1; 
    for (auto elem : result) {
        check = elem;
        if (count == 0) {
            break;
        }
    }
    REQUIRE(check == 1);
}

TEST_CASE("bfs1", "check_immediate_neighbor_0") {
    set<int> result = bfs(graph_, 1);
    REQUIRE(result.find(34) != result.end());
    int count = 0;
    int check = -1; 
    for (auto elem : result) {
        check = elem;
        if (count == 6) {
            break;
        }
    }
    REQUIRE(check == 34);
}
