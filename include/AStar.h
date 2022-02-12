#ifndef PATH_FINDING_ASTAR_H
#define PATH_FINDING_ASTAR_H

class AStar {

public:

    AStar();

    int graphHeight;
    int graphWidth;

    void findPath();

    bool inBounds();

    int manhattanDistance();
    int linearDistance();


};


#endif //PATH_FINDING_ASTAR_H
