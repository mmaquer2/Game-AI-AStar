
#include "../include/AStar.h"
#include "gridNode.cpp"


//create custom grid node for unordered map
struct gridNode {
    int x;
    int y;
};

//override equality operator for gridNode
bool operator==(const gridNode& lhs, const gridNode& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

//gridNode hash function for unordered map
struct gridHash {
    std::size_t operator()(const gridNode& id) const noexcept {
        return std::hash<int>()(id.x ^ (id.y << 1));
    }
};

template<>
struct std::hash<gridNode>
{
    std::size_t operator()(gridNode const& current) const noexcept
    {
        std::size_t h1 = std::hash<int>{}(current.x);
        std::size_t h2 = std::hash<int>{}(current.y);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};


//AStar Constructor function
AStar::AStar() {

    vector<vector<char>> inputMap;
    string loc;
    string modeType, heuristicType;
    int start[2], end[2];

    //cout << "Enter the location of the file:";
    //cin >> loc;
    //readMap(loc,inputMap);
    readMap("/Users/michaelmaquera/school/a-star/data/project1.txt", inputMap);

    Graph nodeGraph(inputMap);// create graph of nodes

    cout << endl;
    cout << "the input map is:\n";
    PrintMap(inputMap);

    //modeType = "Standard";
    //eMode mode = convertMode(modeType);
    //heuristicType = "Manhattan";
    //eHeuristic heuristic = convertHeuristic(heuristicType);

    // Start Coordinates:
    start[0] = 0;
    start[1] = 0;
    cout << endl;

    //End Coordinates:
    end[0] = 2;
    end[1] = 2;

    findPath(inputMap, start, end, "Standard", "manhattan", nodeGraph);

}



// A-star find path function
void AStar::findPath(const vector<vector<char>> &inputMap, int *start, int *destination, string mode, string heuristic,
             Graph nodeGraph) {

    vector<Node> openSet; //container for tracking currently extended nodes
    vector<Node> closedSet; //container for tracking exhausted nodes
    vector<Node> unPassable; //container for holding discovered unpassable noes

    vector<gridNode> finalMap;
    vector<vector<char>> outputMap = inputMap;
    unordered_map<gridNode, gridNode> cameFrom; // map <key, value pair>   hash(key) = value, container for backtracking nodes


    //unordered_map<Node, int> gScore;
    //unordered_map<Node, int> fScore;

    int startX, startY, endX, endY;
    startX = start[0];
    startY = start[1];
    endX = destination[0];
    endY = destination[1];

    using namespace chrono;
    steady_clock::time_point clock_begin = steady_clock::now(); // Start the timer

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

    openSet.push_back(startNode); //insert start node to open container
    bool pathDiscovered = false; // set discovered path boolean to false

    //start path search
    while (!openSet.empty()) {

        int currentIndex = findLowestFValue(openSet);  //find the index of the lowest f value node, in the openSet
        Node currentNode = openSet[currentIndex]; //get the best possible f value from the node
        currentNode.expanded = true; // set the current node expanded flag to true
        currentNode.discovered = true; // set the temp node to discovered flag to true

        openSet.erase(openSet.begin()+currentIndex); //remove the current node from the openSet
        closedSet.push_back(currentNode); //insert current node into the closedSet

        //calculate the f,g,h of the current node.
        currentNode.g = distanceToNeighbor(currentNode.xCoord, currentNode.yCoord,startX,startY);
        if(heuristic == "manhattan"){
            currentNode.h = manhattanDistance(currentNode.xCoord, currentNode.yCoord, endX, endY,currentNode.nodeCost);
        } else {
            currentNode.h = linearDistance(currentNode.xCoord, currentNode.yCoord, endX, endY, currentNode.nodeCost);
        }
        currentNode.f = currentNode.g + currentNode.h + currentNode.nodeCost;

        cout << "current node data" << endl;
        cout << currentNode.xCoord << "," << currentNode.yCoord << endl;
        cout<< " current g: "<< currentNode.g;
        cout<< " current h: "<< currentNode.h;
        cout<< " current f: "  << currentNode.f << endl;

        //pass back the node reference to the graph matrix
        int x = currentNode.xCoord;
        int y = currentNode.yCoord;
        nodeGraph.graph[x][y] = currentNode;

        //check if destination has been reached
        if (currentNode.getLocation() == endNode.getLocation() ) {
            std::cout << "End node found!" << endl;
            pathDiscovered = true; //the closed set now contains the final path from start to finish

            gridNode star, en;
            star.x = startX;
            star.y = startY;
            en.x = endY;
            en.y = endY;

            // make best path map from current node
             //container for final path

            //test to print entire
            cout << "printing nodes after end." << endl;
            for (auto const& element : cameFrom){
                cout<< "key: "<< element.first.x << element.first.y << " value: ";
               std::cout << element.second.x << "," << element.second.y << endl;  // Write to file or whatever you want to do
            }

            gridNode temp;
            temp.x = currentNode.xCoord;
            temp.y = currentNode.yCoord;
            while(temp.x != star.x && temp.y != star.y){
                temp = cameFrom[temp];
                cout <<"temp: " << temp.x << temp.y<< endl;
                finalMap.push_back(temp);
            }



            for(int i = 0; i < finalMap.size(); i++){
                gridNode temp = finalMap[i];
                outputMap[temp.x][temp.y] = '+';

            }


            //vector<Node> completePath = makePath(startNode, endNode);  //reconstruct the final path from start to end
            break;
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
                    } else{
                       int tentativeCost = currentNode.g + distanceToNeighbor(currentNode.xCoord,currentNode.yCoord, tempNeighbor.xCoord,tempNeighbor.yCoord) + tempNeighbor.nodeCost;
                       bool openListStatus = searchOpenList(tempNeighbor, openSet);
                       //check if the new cost is less than the neighbor or is not in the open list
                       if ((tentativeCost <  currentNode.g) || !openListStatus ) {
                           //calculate f,g,h values
                           tempNeighbor.g = tentativeCost;
                           tempNeighbor.h = manhattanDistance(tempNeighbor.xCoord, tempNeighbor.yCoord, endX, endY,tempNeighbor.nodeCost);
                           tempNeighbor.f = tempNeighbor.g + tempNeighbor.h;

                           //set parent and neighbor node relationships
                           tempNeighbor.parentNode = new Node(0,0);
                           tempNeighbor.parentNode = &currentNode;
                           tempNeighbor.parentLocation = {currentNode.xCoord, currentNode.yCoord};

                           //pass reference back into graph matrix
                           nodeGraph.graph[tempNeighbor.xCoord][tempNeighbor.yCoord] = tempNeighbor;

                           cout <<"neighbor: " <<tempNeighbor.xCoord << "," << tempNeighbor.yCoord << " temp g: "<< tempNeighbor.g << " temp h: "<< tempNeighbor.h << " temp f: "  << tempNeighbor.f << endl;

                           //pass current and neighbor nodes into cameFrom hash map
                           gridNode curr, neighbor;
                           curr.x = currentNode.xCoord;
                           curr.y = currentNode.yCoord;
                           neighbor.x = tempNeighbor.xCoord;
                           neighbor.y = tempNeighbor.yCoord;

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
    std::cout << "It took " << seconds << " seconds.";
    std::cout << endl;

    if (!pathDiscovered) {
        cout << "A path could not be found with the given graph" << endl;
    }
    else {

         // copy inputMap

        //just display the path
        if (mode == "Standard") {
           // outputMap[startX][startY] = 's';
           // outputMap[endX][endY] = 'd';


        }

        //display path and expanded nodes
        if (mode == "Expanded") {

           // for(auto temp : closedSet){
            //    outputMap[temp.xCoord][temp.yCoord] = '+';
           // }


        }

        //display path, expanded nodes, and touched nodes
        if (mode == "All") {

            //write the final path to the output map
            for(auto temp : closedSet){
               // outputMap[temp.xCoord][temp.yCoord] = '+';
            }

            //iterate through the examined/modified inputMap and
            for(int i = 0; i < nodeGraph.graph.size(); i++){

                for(int j = 0; j < nodeGraph.graph[i].size();j++){
                    Node temp = nodeGraph.graph[i][j];

                    //set discovered nodes
                    if(temp.discovered){
                        //outputMap[i][j] = 't';
                    }

                    //set expanded nodes
                    if(temp.expanded){
                       // outputMap[i][j] = 'e';
                    }

                }
            }
        }

        //set start and end nodes on the output map
       outputMap[startX][startY] = 's';
        outputMap[endX][endY] = 'd';

        std::cout << endl;
        std::cout << "the output map is:";
        std::cout << endl;
        PrintMap(outputMap);
    }

}



bool AStar::inBounds(int x, int y, int height,int width) {
    if( (x >= 0) &&
        (y >= 0) &&
        (x <= height ) &&
        (y <= height ) &&
        (x <= width ) &&
        (y <= width ))

    {return true;}
    else {return false;}
}

int AStar::manhattanDistance(int x, int y, int endX, int endY,int weight) {
    int dx = fabs( x - endX);
    int dy = fabs(y - endY);
    int avgDiff = 10; // the avg difference of all nodes
    int result = dx + dy;
    return result;

}


int AStar::linearDistance(int x, int y, int endX, int endY,int weight) {

    int dx = fabs( x - endX);
    int dy = fabs(y - endY);
    int avgDiff = 10;
    int result = avgDiff * (dx * dx + dy * dy);
    return result;
}

int AStar::getHeight() {
    return graphHeight;
}

int AStar::getWidth() {
    return graphWidth;
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

//function to search the open list for neighbor nodes
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


//function to search the closed list for present nodes
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

int AStar::gValueDistance(int x, int y, int startX, int startY,int weight) {
    int dx = fabs( x - startX);
    int dy = fabs(y - startY);
    int gValue = (dx + dy) + weight;
    return gValue;

}

//calculate the current distance to neighbor values
int AStar::distanceToNeighbor(int currentX, int currentY, int neighborX, int neighborY) {
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

//function to return the final best path in terms of x,y values
vector<array<int,2>> makePath(unordered_map<int, int> , Node current){
    vector<array<int,2>> finalPath;




    return finalPath;
}



