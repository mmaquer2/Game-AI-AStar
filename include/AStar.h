

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

    int graphHeight;
    int graphWidth;

    AStar();

    void findPath(const vector<vector<char>> &inputMap, int *start, int *destination, string mode, string heuristic,
                  Graph nodeGraph);

    bool inBounds(int x, int y, int height,int width);
    int manhattanDistance(int x, int y, int endX, int endY);
    int linearDistance(int x, int y, int endX, int endY);

    int getHeight();
    int getWidth();
};


#endif //PATH_FINDING_ASTAR_H
