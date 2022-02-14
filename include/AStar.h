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

    int findLowestFValue(vector<Node> input);

    bool inBounds(int x, int y, int height,int width);
    int manhattanDistance(int x, int y, int endX, int endY, int weight);
    int linearDistance(int x, int y, int endX, int endY, int weight);
    int gValueDistance(int x, int y, int startX, int startY, int weight);

    bool searchClosedList(Node input, vector<Node> closedSet);

    int getHeight();
    int getWidth();

    bool searchOpenList(Node input, vector<Node> closedSet);

    int distanceToNeighbor(int currentX,int currentY, int neighborX, int neighborY);

    vector<Node> makePath(Node start, Node end);

    vector<Node> reconstructPath(unordered_map<Node, int> , Node current);


};


#endif //PATH_FINDING_ASTAR_H
