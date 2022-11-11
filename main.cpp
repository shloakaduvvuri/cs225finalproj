#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int sum = 0;
    int x;
    ifstream inFile;
    inFile.open("roadNet-TX.txt");
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (inFile >> x) {
        std::cout << x << std::endl;
    }
    inFile.close();
    std::cout << "Sum = " << sum << std::endl; 

    return 0;
}