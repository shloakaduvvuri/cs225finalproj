#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
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
    map<int, vector<int>> graph_;
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
    // std::cout << graph_.size() << std::endl;
    // std::cout << graph_.at(1).size() << std::endl;

    for (auto node_relation : graph_) {
        sort(node_relation.second.begin(), node_relation.second.end());
    }
    for (auto node_relation : graph_) {
    //     std::cout << "City " << node_relation.first << " Connects To: " << std::endl;
    //     std::cout << "{ ";
        //for (int neighbor : node_relation.second) {
            //std::cout << neighbor << " ";
        //}
    //     std::cout << "}" << std::endl;
    }
    // std::cout << "}" << std::endl;
    return 0;   
}

