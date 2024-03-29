#ifndef PATH_FINDING_ASTAR_H
#define PATH_FINDING_ASTAR_H
#include <chrono>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>
#include "../include/Project1.h"
#include "../include/Node.h"
#include "../include/Graph.h"
#include <math.h>

// create custom grid node for the unordered map container
struct gridNode {
    int x;
    int y;
};

// class to represent the A Star path finding program
class AStar {

public:
    AStar();
    int graphHeight;
    int graphWidth;

    void findPath(const vector<vector<char>> &inputMap, int *start, int *destination, string mode, string heuristic,
                  Graph nodeGraph);

    bool inBounds(int x, int y, int height,int width); // determines if a node is within legal bounds of the graph
    int distanceToNeighbor(int currentX,int currentY, int neighborX, int neighborY, int weight); // calculate the distance between neighbor nodes
    int manhattanDistance(int x, int y, int endX, int endY, int weight);
    int linearDistance(int x, int y, int endX, int endY, int weight);

    bool searchClosedList(Node input, vector<Node> closedSet);
    bool searchOpenList(Node input, vector<Node> closedSet);
    int findLowestFValue(vector<Node> input);

    void createOutputMap(string mode, Graph finalGraph, vector<vector<char>> outputMap, vector<gridNode> finalMap,int startX,int startY, int endX,int endY);

};


#endif //PATH_FINDING_ASTAR_H
