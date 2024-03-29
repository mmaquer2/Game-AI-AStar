#include "../include/AStar.h"

// override equality operator for gridNode
bool operator==(const gridNode& lhs, const gridNode& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
// override not equals operator for gridNode
bool operator!=(const gridNode& lhs, const gridNode& rhs){
    return lhs.x != rhs.x && lhs.y != rhs.y;
}
// hash function for gridNode
template<> struct std::hash<gridNode> {
    std::size_t operator()(gridNode const& current) const noexcept {
        std::size_t h1 = std::hash<int>{}(current.x);
        std::size_t h2 = std::hash<int>{}(current.y);
        return h1 ^ (h2 << 16);
    }
};
//AStar Constructor function
AStar::AStar() {

    //declare class variables
    vector<vector<char>> inputMap;
    string loc;
    string hType;
    string mode;
    string modeType, heuristicType;
    int start[2], end[2];
    int sX, sY, eX, eY;

    cout << "Enter the location of the file:";
    cin >> loc;

    //"/Users/michaelmaquera/school/a-star/data/project1.txt"
    readMap(loc, inputMap);

    cout << "enter the heuristic type: m = manhattan, l = linear" << endl;
    cin>>hType;
    cout << "enter the output map type: a = all, e = expanded, s = standard" << endl;
    cin >> mode;

    cout << "Enter start x"<< endl;
    cin >> sX;

    cout << "Enter start y:" << endl;
    cin >> sY;

    cout <<"Enter end x" << endl;
    cin >> eX;

    cout << "Enter end y" << endl;
    cin >> eY;

    Graph nodeGraph(inputMap);// create graph of nodes

    if(nodeGraph.width != nodeGraph.height){
        cout <<" ERROR: you must submit a graph with equal width and height" << endl;
        return;
    }

    graphWidth = nodeGraph.width; //pass height and width to A Star class
    graphHeight = nodeGraph.height;

    cout << endl;
    cout << "the input map is:\n";
    PrintMap(inputMap);

    // Start Coordinates:
    start[0] = sX;
    start[1] = sY;
    cout << endl;

    //End Coordinates:
    end[0] = eX; // width (x)
    end[1] = eY; // height (y)

    findPath(inputMap, start, end, mode, hType, nodeGraph);

}

// A-star find path function
void AStar::findPath(const vector<vector<char>> &inputMap, int *start, int *destination, string mode, string heuristic,
             Graph nodeGraph) {

    vector<Node> openSet; //container for tracking currently extended nodes
    vector<Node> closedSet; //container for tracking exhausted nodes
    vector<Node> unPassable; //container for holding discovered unpassable noes

    vector<gridNode> finalMap; // vector to hold final map
    vector<vector<char>> outputMap = inputMap; // copy input map
    unordered_map<gridNode, gridNode> cameFrom; // map <key, value pair>   hash(key) = value, container for backtracking nodes

    int startX, startY, endX, endY;
    startX = start[0];
    startY = start[1];
    endX = destination[0];
    endY = destination[1];

    //check if start and end node are in bounds
    if(!inBounds(startX, startY, nodeGraph.height, nodeGraph.width) ||
       (!inBounds(endX, endY, nodeGraph.height, nodeGraph.width))){
        cout <<" ERROR: selected an out of bounds node as the start or end node" << endl;
        return;
    }

    Node startNode = nodeGraph.graph[startX][startY];  //get the starting node from the graph
    Node endNode = nodeGraph.graph[endX][endY];  //get the end node from the graph

    //check if start and end nodes are passable
    if(!startNode.passable || !endNode.passable){
        cout <<" ERROR: selected a unpassable node as the start or end node" << endl;
        return;
    }

    using namespace chrono; // Start the timer
    steady_clock::time_point clock_begin = steady_clock::now();

    openSet.push_back(startNode); //insert start node to open container
    bool pathDiscovered = false; // set discovered path boolean to false

    //set the starting node for reconstructing the path
    gridNode star = {startX, startY};

    //start path search
    while (!openSet.empty()) {

        int currentIndex = findLowestFValue(openSet);  //find the index of the lowest f value node, in the openSet
        Node currentNode = openSet[currentIndex]; //get the best possible f value from the node
        currentNode.expanded = true; // set the current node expanded flag to true
        currentNode.discovered = true; // set the temp node to discovered flag to true

        openSet.erase(openSet.begin()+currentIndex); //remove the current node from the openSet
        closedSet.push_back(currentNode); //insert current node into the closedSet

        //calculate the f,g,h of the current node.
        currentNode.g = distanceToNeighbor(currentNode.xCoord, currentNode.yCoord,startX,startY,currentNode.nodeCost);
        if(heuristic == "manhattan"){
            currentNode.h = manhattanDistance(currentNode.xCoord, currentNode.yCoord, endX, endY,currentNode.nodeCost);
        } else {
            currentNode.h = linearDistance(currentNode.xCoord, currentNode.yCoord, endX, endY, currentNode.nodeCost);
        }
        currentNode.f = currentNode.g + (currentNode.nodeCost *currentNode.h * 2);

        //uncomment for current node details
        //cout <<"Current: " << currentNode.xCoord << "," << currentNode.yCoord << "  g: "<< currentNode.g << " temp h: "<< currentNode.h << " temp f: "  << currentNode.f << endl;

        //pass back the node reference to the graph matrix
        int x = currentNode.xCoord;
        int y = currentNode.yCoord;
        nodeGraph.graph[x][y] = currentNode;

        //check if destination has been reached
        if (currentNode.getLocation() == endNode.getLocation() ) {
            std::cout << "End node found!" << endl;
            pathDiscovered = true; //the closed set now contains the final path from start to finish

            //reconstruct the path working backwards from the end node
            gridNode temp = {endX,endY}; //work backwards from the end node
            int count = 0;
            int maxPathLength = graphHeight * graphWidth; //the path will not be greater than the all nodes in the graph
            while(count != maxPathLength){
                if(temp == star){
                   break;
                }
                temp = cameFrom[temp];
                finalMap.push_back(temp);
                count = count + 1;
            }

            //create the output map
            createOutputMap(mode,nodeGraph,inputMap,finalMap,startX, startY,  endX, endY);

            //break pathfinding, program complete
            return;

        }

        // Scan through the all neighbors of the current node
        for (int i = 0; i < currentNode.neighbors.size() ; ++i) {
            array<int, 2> tempCoors = currentNode.neighbors[i]; // get the coordinates of the neighbor
            //check if the neighbor is valid within the graph boundary and is passable
            if (inBounds(tempCoors[0], tempCoors[1], nodeGraph.height, nodeGraph.width)  ) {
                Node tempNeighbor = nodeGraph.graph[tempCoors[0]][tempCoors[1]]; //get the current neighbor node

                //check if this neighbor node is already in the closed list
                if(!searchClosedList(tempNeighbor,closedSet)){

                    tempNeighbor.discovered = true; //set the neighbor node to discovered

                    if(!tempNeighbor.passable){
                        unPassable.push_back(tempNeighbor);
                    } else {

                       int tentativeCost = currentNode.g + distanceToNeighbor(currentNode.xCoord,currentNode.yCoord, tempNeighbor.xCoord,tempNeighbor.yCoord, tempNeighbor.nodeCost);
                       bool openListStatus = searchOpenList(tempNeighbor, openSet);

                       //check if the new cost is less than the neighbor or is not in the open list
                       if ((tentativeCost <  currentNode.g) || !openListStatus ) {

                           //calculate f,g,h values
                           tempNeighbor.g = tentativeCost;
                           if(heuristic == "manhattan"){
                               tempNeighbor.h = manhattanDistance(tempNeighbor.xCoord, tempNeighbor.yCoord, endX, endY,tempNeighbor.nodeCost);
                           } else {
                               tempNeighbor.h = linearDistance(tempNeighbor.xCoord, tempNeighbor.yCoord, endX, endY,tempNeighbor.nodeCost);
                           }

                           tempNeighbor.f = tempNeighbor.g + (tempNeighbor.nodeCost * tempNeighbor.h);

                           //set parent and neighbor node relationships
                           tempNeighbor.parentNode = new Node(0,0);
                           tempNeighbor.parentNode = &currentNode;
                           tempNeighbor.parentLocation = {currentNode.xCoord, currentNode.yCoord};

                           //pass reference back into graph matrix
                           nodeGraph.graph[tempNeighbor.xCoord][tempNeighbor.yCoord] = tempNeighbor;

                           //uncomment for tempNeighbor details
                           //cout <<"neighbor: " <<tempNeighbor.xCoord << "," << tempNeighbor.yCoord << " temp g: "<< tempNeighbor.g << " temp h: "<< tempNeighbor.h << " temp f: "  << tempNeighbor.f << endl;

                           //pass current and neighbor nodes into cameFrom hash map
                           gridNode curr = {currentNode.xCoord, currentNode.yCoord };
                           gridNode neighbor = { tempNeighbor.xCoord, tempNeighbor.yCoord};
                           cameFrom[neighbor] = curr;

                           openSet.push_back(tempNeighbor); // add neighbor node to the open set

                       }
                    }
                }
            }
        }
    }

    // Stop the timer
    steady_clock::time_point clock_end = steady_clock::now();
    steady_clock::duration time_span = clock_end - clock_begin;
    double seconds = double(time_span.count()) * steady_clock::period::num / steady_clock::period::den;

    std::cout << endl;
    std::cout << "Elapsed Time: " << seconds << " seconds." << endl;

    // program has failed to find a path if it reaches this line
    if (!pathDiscovered) {
        cout << "A path could not be found with the given graph" << endl;
    }


}

// check if a map node is in bounds of the map
bool AStar::inBounds(int x, int y, int height,int width) {
    if( (x >= 0) &&
        (y >= 0) &&
        ( x <= width) &&
        (y <= height) &&
        ( x<= height) &&
        (y<=width))
    { return true; }
    else { return false; }
}

// calculate the manhattan distance
int AStar::manhattanDistance(int x, int y, int endX, int endY,int weight) {
    int dx = fabs( x - endX);
    int dy = fabs(y - endY);
    int avgDiff = 10; // the avg difference of all nodes
    int result = dx + dy + weight;
    return result;

}

// calculate the linear distance
int AStar::linearDistance(int x, int y, int endX, int endY,int weight) {

    int dx = fabs( x - endX);
    int dy = fabs(y - endY);

    int result =  sqrt(dx * dx + dy * dy) + weight;
    return result;
}


// helper function to find the current node with the lowest f value in the open set
int AStar::findLowestFValue(vector<Node> input) {

    int min = input[0].f;
    Node lowestF(0,0);
    int lowestIndex = 0;

    //if the openSet vector only has the size of one
    if(input.size() == 1){
        lowestIndex = 0;
        return 0;
    }

    //search for the lowest f value in the open set vector
    for(int i = 0; i < input.size(); i++){
        if(input[i].f < min){
            lowestF = input[i];
            lowestIndex = i;
        }
    }

    return lowestIndex;
}

// function to search the open list for neighbor nodes
bool AStar::searchOpenList(Node input,vector<Node> openSet ) {
    bool foundStatus = false;
    for(auto temp : openSet){
        int tempX = temp.xCoord;
        int tempY = temp.yCoord;
        if((tempX == input.xCoord) && (tempY == input.yCoord) ){
            foundStatus = true;
            return foundStatus;
        }
    }
    return foundStatus;
}


// function to search the closed list for present nodes
bool AStar::searchClosedList(Node input,vector<Node> closedSet ) {
    bool foundStatus = false;
    for(auto temp : closedSet){
        int tempX = temp.xCoord;
        int tempY = temp.yCoord;
        if((tempX == input.xCoord) && (tempY == input.yCoord) ){
            foundStatus = true;
            return foundStatus;
        }
    }
    return foundStatus;
}

// calculate the current node's distance to a neighbor node
int AStar::distanceToNeighbor(int currentX, int currentY, int neighborX, int neighborY, int weight) {
    int dValue =0;
    int dx = fabs( currentX - neighborX);
    int dy = fabs(currentY - neighborY);

    if(dx > dy){
        dValue = 14 * dy + 10*(dx - dy);
    } else{
        dValue = 14 * dx + 10*(dy - dx);
    }

    return dValue;
}


//create the output map based on the given path and found nodes
void AStar::createOutputMap(string mode, Graph final, vector<vector<char>> outputMap,vector<gridNode> finalMap, int startX,int startY, int endX,int endY) {

    //display path and expanded nodes
    if (mode == "e") {
        //iterate through the examined/modified inputMap and
        for(int i = 0; i < final.graph.size(); i++){

            for(int j = 0; j < final.graph[i].size();j++){
                Node temp = final.graph[i][j];

                //set expanded nodes
                if(temp.expanded){
                    outputMap[i][j] = 'e';
                }

            }
        }

    }

    //display path, expanded nodes, and touched nodes
    if (mode == "a") {

        //iterate through the examined/modified inputMap and
        for(int i = 0; i < final.graph.size(); i++){

            for(int j = 0; j < final.graph[i].size();j++){
                Node temp = final.graph[i][j];

                //set discovered nodes
                if(temp.discovered){
                    outputMap[i][j] = 't';
                }

                //set expanded nodes
                if(temp.expanded){
                    outputMap[i][j] = 'e';
                }
            }
        }
    }

    // print path onto output map
    for(int i = 0; i < finalMap.size(); i++){
        gridNode curr = finalMap[i];
        outputMap[curr.x][curr.y] = '+';
    }

    //set start and end nodes on the output map
    outputMap[startX][startY] = 's';
    outputMap[endX][endY] = 'd';

    std::cout << endl;
    std::cout << "The Output Map:";
    std::cout << endl;
    PrintMap(outputMap);

}




