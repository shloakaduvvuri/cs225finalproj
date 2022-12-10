#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <climits>
#include <set>

using namespace std;

int main() {
    //data parsing
    map<int, vector<int>> graph_;
    int index = 0;
    //int sum = 0;
    int key;
    int x;
    ifstream inFile;
    inFile.open("roadNet-TX.txt");
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (inFile >> x) {
        //std::cout << x << std::endl;
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
    cout << "Data Parsing - Adjacency List - Graph Implementation" << endl;
    int print = 0; 
    for (auto node_relation : graph_) {
    std::cout << "City " << node_relation.first << " Connects To: " << std::endl;
    print++;
    std::cout << "{ ";
        for (int neighbor : node_relation.second) {
            std::cout << neighbor << " ";
        }
        std::cout << "}" << std::endl;
        if (print == 100) {
            break;
        }
    }
    std::cout << "}" << std::endl;

    //bfs
    cout << "Breadth First Search Traversal" << endl;
    int from = 0;
    queue<int> q; 
    set<int> visited;
    q.push(from);
    //visited.push_back(from);
    while (!q.empty()) {
        int curr = q.front();
        std::cout << curr << " ";
        q.pop();
        vector<int> tovisit = graph_.at(curr);
        for (auto i : tovisit) {
            if (visited.find(i) == visited.end()) {
                q.push(i);
                visited.insert(i);
            }
        }
    }
    cout << "" << endl;
    // for (int v : visited) {
    //     std::cout << v << " ";
    // }
    std::cout << '\n';
    //djikstras
    cout << "Djikstra's Shortest Path - Distance of 100 Cities from Source" << endl;
    int source = 0;
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
    for (auto v : distances) {
        std::cout << v.first << "->" << v.second << ", ";
    }

    std::cout << '\n';
    
    //euler-path
    cout << "Eulerian Path - Add Specificity" << endl;

}