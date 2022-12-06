#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
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

    //BFS TRAVERSAL
    queue<int> q; 
    vector<int> visited;
    int from = 0; 
    //int arrive = 1; 
    q.push(from);
    visited.push_back(from);
    //int count = 0;
    //bool finished = false;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        vector<int> tovisit = graph_.at(curr);
        for (unsigned i = 0; i < tovisit.size(); i++) {
            if (find(visited.begin(), visited.end(), tovisit.at(i)) == visited.end()) {
                /*if (tovisit.at(i) == arrive) {
                    count++;
                    std::cout << "Path Length: " << count << std::endl;
                    finished = true;
                    break;
                }*/
                q.push(tovisit.at(i));
                visited.push_back(tovisit.at(i));
                //count++;
            }
        }
        /*if (finished) {
            break;
        }*/
    }
    for (int v : visited) {
        std::cout << v << " ";
    }
    std::cout << '\n';

    return 0;   
}

