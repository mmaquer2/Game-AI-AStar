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

class AStar {

public:
    AStar();
    int graphHeight;
    int graphWidth;

    void findPath(const vector<vector<char>> &inputMap, int *start, int *destination, string mode, string heuristic,
                  Graph nodeGraph);
    vector<array<int,2>> makePath(unordered_map<int, int> , Node current);

    bool inBounds(int x, int y, int height,int width);
    int distanceToNeighbor(int currentX,int currentY, int neighborX, int neighborY);
    int manhattanDistance(int x, int y, int endX, int endY, int weight);
    int linearDistance(int x, int y, int endX, int endY, int weight);
    int gValueDistance(int x, int y, int startX, int startY, int weight);

    bool searchClosedList(Node input, vector<Node> closedSet);
    bool searchOpenList(Node input, vector<Node> closedSet);
    int findLowestFValue(vector<Node> input);

};


#endif //PATH_FINDING_ASTAR_H
