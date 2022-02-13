#ifndef PROJECT_HPP 
#define PROJECT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void static readMap(const std::string& filename, std::vector<std::vector<char>> &PathMap)
{

    std::ifstream file(filename);
    std::vector<char> row;
    std::string input;
    while (file >> input) {
        row.clear();
        for (char i : input) {
            row.push_back(i);
        }
        PathMap.insert(PathMap.begin(), row);
    }

    //To check if there are equal number of values in each row.
    size_t length = PathMap[0].size();
    for (size_t i = 1; i < PathMap.size(); i++) {
        if (length != PathMap[i].size()) {
            printf("Error in input file.");
            PathMap.clear();
            return;
        }
    }
}

void static PrintMap(std::vector<std::vector<char>> PathMap) {
    for (std::vector<char> name : PathMap)
    {
        for (char c : name)
        {
            std::cout << c;
        }
        std::cout << endl;

    }
}

enum eMode { Standard, Expanded, All };
enum eHeuristic { StraightLine, Manhattan };


#endif