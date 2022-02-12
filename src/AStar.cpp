
#include "AStar.h"



void AStar::findPath(const vector<vector<char>> &inputMap, int *start, int *destination, eMode mode,
                     eHeuristic heuristic, Graph nodeGraph) {





}


bool AStar::inBounds(int x, int y, int height,int width) {
    if( (x >= 0) &&
        (y >= 0) &&
        (x<= height) &&
        (y <= height) &&
        (x <=width) &&
        (y <= width))
    {return true;}
    else {return false;}
}

int AStar::manhattanDistance(int x, int y, int endX, int endY) {
    int dx = fabs( x - endX);
    int dy = fabs(y - endY);
    int avgDiff = 2; // the avg difference of all nodes

    return avgDiff * (dx + dy);

}


int AStar::linearDistance(int x, int y, int endX, int endY) {


    return 0;
}

int AStar::getHeight() {

    return graphHeight;
}

int AStar::getWidth() {

    return graphWidth;
}