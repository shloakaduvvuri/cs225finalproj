#include <catch2/catch_test_macros.hpp>
#include "bfs.h"

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
}

TEST_CASE("bfs", "bfs_basic_map") {
  // replace this section with makeMap() to create actual graph
  vector<int> tmp;
  tmp.push_back(2);
  tmp.push_back(3);
  tmp.push_back(4);
  map<int, vector<int>> graph_;
  graph_.insert({1,tmp});

  REQUIRE(travelNode(1, 2) == 1);
}
