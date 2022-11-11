#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
using namespace std;

int main() {
    int sum = 0;
    int index = 0;
    int key;
    int x;
    ifstream inFile;
    inFile.open("roadNet-TX.txt");
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    map<int, int> connections;
    while (inFile >> x) {
        //std::cout << x << std::endl;
        if (index % 2 == 0) {
            key = x;
        } else if (index % 2 == 1) {
            connections.insert(make_pair(key, x));
        }
        index++;
    }
    inFile.close();
    std::cout << "Sum = " << sum << std::endl; 
    // for (auto connection : connections) {
    //     std::cout << "From: " << connection.first << " To: " << connection.second << std::endl;
    // }
    std::cout << connections.size() << std::endl;
    return 0;
}

