#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <climits>
#include <stack>
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
    // for (auto node_relation : graph_) {
    // std::cout << "City " << node_relation.first << " Connects To: " << std::endl;
    // std::cout << "{ ";
    //     for (int neighbor : node_relation.second) {
    //         std::cout << neighbor << " ";
    //     }
    //      std::cout << "}" << std::endl;
    // }
    // std::cout << "}" << std::endl;

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
    cout << "Djikstra's Shortest Path - Closest 100 Nodes to Source" << endl;
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
     bool isConnected = true;
    set<int> haveVisited;
  
    int idx=0;
    bool done =false;
   
    for(auto elem:graph_){
    
        if(graph_.at(elem.first).size() > 0&&(!done)){
            idx=elem.first;
            done=true;
        }
    }
 
   
    stack<int> s;
    s.push(idx);
    while (!s.empty()) {
        int c = s.top();
        
        s.pop();
        vector<int> toVisit = graph_.at(c);
        for (auto i : toVisit) {
            if (haveVisited.find(i) == haveVisited.end()) {
                s.push(i);
                haveVisited.insert(i);
               
            }
        }
    }
    //end dfs
    if(haveVisited.size()!=graph_.size()){
        isConnected=false;
    }
 
    bool isEulerian=true;
    //end isconnection
    //start iseulerian
    if (isConnected == false){
        std::cout<<"NOT EULERIAN BECAUSE NOT CONNECTED"<<std::endl;
        isEulerian=false;
    }
    int odd = 0;
    set<int>::iterator itr;
    for(itr=haveVisited.begin();itr!=haveVisited.end();itr++){
            if(graph_.at(*itr).size()%2==1){
                odd++;
            }

    }
   
   
    if(odd>2){
        std::cout<<"NOT EULERIAN BECAUSE MORE THAN TWO NODES OF ODD DEGREE"<<std::endl;
        isEulerian=false;
    } else if(odd==0){
        std::cout<<"EULERIAN CIRCUIT"<<std::endl;
    } else{
        std::cout<<"EULERIAN PATH"<<std::endl;
    }
 
  
// TEST_CASE("graph", "check_structure") {
    //unsigned actual_num_nodes = 1379917;
    int actual_num_edges = 1921660;
    int undirected_edges = actual_num_edges*2;
    //REQUIRE(graph_.size() == actual_num_nodes);
    /* the number of edges represents the total number
    of connections across all the nodes 
    (total num of elements in all values vectors)
    */
   count = 0;
    for (auto node_neighbors : graph_) {
        count+=node_neighbors.second.size();
    }
    assert (count == undirected_edges);
//}
// 153380, 1
// TEST_CASE("graph2", "check_accuracy") {
    //pulled from dataset info 
    vector<int> neighbors_of_1;
    for (auto c : graph_.at(1)) {
        neighbors_of_1.push_back(c);
    }
    vector<int> correct_1 = {0, 23, 32};
    assert(neighbors_of_1 == correct_1);
// }
//153408, 153376
// TEST_CASE("graph3", "check_undirected") {
    //pulled from dataset info 
    int neighbor_of_153408 = 153376;
    vector<int> to_search = graph_.at(neighbor_of_153408);
    assert(find(to_search.begin(), to_search.end(), 153408) != to_search.end());
// }

// TEST_CASE("djikstra1", "check_source_0") {
    if(distances[0].second == 0){
        std::cout << "passes djikstra1 test 1" << std::endl;
    } else {
        std::cout << "does not pass djikstra1 test 1" << std::endl;
    }
    if(distances[1].second == 1) {
        std::cout << "passes djikstra1 test 2" << std::endl;
    } else {
        std::cout << "does not pass djikstra1 test 2" << std::endl;
    }
    if(distances[2].second == 1) {
        std::cout << "passes djikstra1 test 3" << std::endl;
    } else {
        std::cout << "does not pass djikstra1 test 3" << std::endl;
    }
// }

// TEST_CASE("djikstra2", "check_middle") {
    if(distances[6].second == 76) {
        std::cout << "passes djikstra2 test 1" << std::endl;
    } else {
        std::cout << "does not pass djikstra2 test 1" << std::endl;
    }
    if(distances[27].second == 13) {
        std::cout << "passes djikstra2 test 2" << std::endl;
    } else {
        std::cout << "does not pass djikstra2 test 2" << std::endl;
    }
    if (isEulerian == false) {
        std::cout << "passes Eulerian test 1" << std::endl;
    } else {
        std::cout << "does not pass Eulerian test 1" << std::endl;
    }
//}

// TEST_CASE("bfs1", "check_immediate_neighbor_0") {
    if(visited.find(1) != visited.end()) {
        std::cout << "passes bfs1 test 1" << std::endl;
    } else {
        std::cout << "does not pass bfs1" << std::endl;
    }
// }

// TEST_CASE("bfs2", "check_immediate_neighbor_0") {
    if (visited.find(1) != visited.end()) {
        std::cout << "passes bfs2 test 1" << std::endl;
    } else {
        std::cout << "does not pass bfs2 test 1" << std::endl;
    }
// }

// TEST_CASE("bfs3", "check_immediate_neighbor_0") {
    if(visited.find(34) != visited.end()) {
        std::cout << "passes bfs3 test 1" << std::endl;
    } else {
        std::cout << "does not pass bfs3 test 1" << std::endl;
    }  

//}

std::cout << "all assertions in all test cases passed" << std::endl;
return 0;
}