#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include "bfs.h"
using namespace std;


int BFS::travelNode(int from, int arrive) {
    q.push(from);
    visited.push_back(from);
    int count = 0;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        vector<int> tovisit = cities.at(curr);
        for (int i = 0; i < tovisit.size(); i++) {
            // if (visited.find(tovisit.at(i)) == visited.end()) {
            if (find(visited.begin(), visited.end(), tovisit.at(i)) == visited.end()) {
                if (tovisit.at(i) == arrive) {
                    return count;
                }
                q.push(tovisit.at(i));
                visited.push_back(tovisit.at(i));
                count++;
            }

        }
    }
    return -1; // never arrives
}