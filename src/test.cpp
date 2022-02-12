#include <chrono>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>
#include "../include/Project1.h"
#include "../include/Node.h"
#include "../include/Graph.h"
#include <math.h>

using namespace std;

// helper function to check if a neighbor already exists in the openSet
bool neighborInOpenSet(Graph input, Node node){
    bool status = false;
    //check if the node is not in the openSet
    // for (int i = 0; i < openSet.size(); i++) {
    // Node temp = openSet[i];
    // if (temp == tempNeighbor) {
    //   status = true;
    //}

    //}

    return status;

}


//Helper function to check if node is in bounds
bool inBounds(int x, int y, int height,int width){
    if( (x >= 0) &&
        (y >= 0) &&
        (x<= height) &&
        (y <= height) &&
        (x <=width) &&
        (y <= width))
    {return true;}
    else {return false;}
}

int manhattan(int x, int y, int endX, int endY){
    int dx = fabs( x - endX);
    int dy = fabs(y - endY);
    int avgDiff = 2; // the avg difference of all nodes

    return avgDiff * (dx + dy);


}



// /Users/michaelmaquera/school/a-star/data/project1.txt
void PlanPath(const vector<vector<char>>& inputMap, int start[2], int destination[2], eMode mode, eHeuristic heuristic , Graph nodeGraph )
{
    // Start the timer
    using namespace chrono;
    steady_clock::time_point clock_begin = steady_clock::now();

    vector<Node> cameFrom; //container for track when the current best path
    vector<int> totalCost;

    vector<Node> openSet; //container for tracking currently exmained code
    vector<Node> closedSet; //container for tracking exhausted nodes


    int startX, startY, endX, endY;
    startX = start[0];
    startY = start[1];
    endX = destination[0];
    endY = destination[1];

    Node startNode = nodeGraph.graph[startX][startY];  //get the starting node from the graph
    Node endNode = nodeGraph.graph[endX][endY];  //get the end node from the graph
    
   openSet.push_back(startNode); //insert start node to open container
   bool pathDiscovered = false; // set discovered path boolean to false

    while (!openSet.empty()) {

       Node currentNode = openSet.back(); //get node at front of openList
       currentNode.expanded = true; // set the current node expanded flag to true
       currentNode.discovered = true; // set the temp node to discovered flag to true
       openSet.pop_back(); //remove the top element just received
       closedSet.push_back(currentNode); //insert current node into the closedSet
       cout << "current node cost: " << currentNode.nodeCost << endl; //uncomment to see what neighbors are being tested
       //check if destination has been reached  
       if (currentNode.getLocation() == endNode.getLocation() ) {
           pathDiscovered = true; //the closed set now contains the final path from start to finish
            break;
       }
       for (int i = 0; i < currentNode.neighbors.size(); ++i) {
           array<int, 2> tempCoors = currentNode.neighbors[i]; // get the coordinates of the neighbor
           cout << "current neighbor coordinate: " << tempCoors[0] << tempCoors[1] << endl;
           //check if the neighbor is valid within the graph boundary and is passable
           if (inBounds(tempCoors[0], tempCoors[1], nodeGraph.height, nodeGraph.width)  ) {

               Node tempNeighbor = nodeGraph.graph[tempCoors[0]][tempCoors[1]]; //get the current neighbor node
               tempNeighbor.discovered = true; //set the neighbor node to discovered

               tempNeighbor.g = currentNode.nodeCost + tempNeighbor.nodeCost;
               tempNeighbor.h = manhattan(tempNeighbor.xCoord, tempNeighbor.yCoord, endX, endY);
               tempNeighbor.f = tempNeighbor.g + tempNeighbor.h;


               bool neighborInOpen = false;

               // if this path to the neighbor is better than the previous path
               // calculate the tempNeighbor and current node costs of traveling

               if ((tempNeighbor.f < currentNode.f) || neighborInOpen ) {

                   cout << "accepting the tentative cost of the new neighbor node " << endl;
                   openSet.push_back(tempNeighbor);

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

        // Annotate & print the output map
        //vector<vector<char>> outputMap = inputMap;

        //create a new output file
        string outputPath = "outputPath.txt";
        //s = start node
        //d = destination node
        //+ = path node
        //t = touched/discovered noe
        //e = expnaded nodes

        //iterate through the examined/modified inputMap and

        //TODO Annotate the map based on the mode selected

        if (mode == Expanded) {

            std::cout << " creating expanded view";

        }

        if (mode == All) {

            std::cout << " creating all view";


        }

        std::cout << endl;
        std::cout << "the output map is:";
        std::cout << endl;
        PrintMap(inputMap);

    }

}



int Test() {

    vector<vector<char>> inputMap;
    string loc;
    string modeType, heuristicType;
    int start[2], end[2];

    cout << "Enter the location of the file:";
    cin >> loc;
    //loc = "project1.txt";
    readMap(loc, inputMap);


    cout << "reading nodeGraph" << endl;

    Graph nodeGraph(inputMap);// create graph of nodes


    cout << endl;
    cout << "the input map is:\n";
    PrintMap(inputMap);

    modeType = "All";
    eMode mode = convertMode(modeType);

    heuristicType = "Manhattan";
    eHeuristic heuristic = convertHeuristic(heuristicType);


    // Start Coordintes:
    start[0] = 0;
    start[1] = 0;
    cout << endl;

    //End Coordinates:
    end[0] = 0;
    end[1] = 1;

    //Create starting hValues
    nodeGraph.calculateHValues(heuristicType, end);

    PlanPath(inputMap, start, end, mode, heuristic, nodeGraph);

    return 0;
}


// C:\Users\mikem\source\repos\gameAI_project_one\Project1\data\project1.txt
void testNode() {

    //read input map function...
    vector<vector<char>> inputMap;
    string loc;
    cout << "Enter the location of the file:";
    cin >> loc;
    //loc = "project1.txt";
    readMap(loc, inputMap);

    int start[2];
    start[0] = 1;
    start[1] = 1;

    //create test start node
    Node startNode(start[0], start[1]); //create start node 

    //test get start location
   // vector<int> temp = startNode.getLocation();
    //std::cout << temp[1] << endl;

    //test get all neighbor nodes
    startNode.calculateNeighbors();
    //std::cout <<" right node:" <<startNode.neighbors[0].xCoord << "," << startNode.neighbors[0].yCoord << endl;
    //std::cout << " left node:" << startNode.neighbors[1].xCoord << "," << startNode.neighbors[1].yCoord << endl;
    //std::cout << " up node:" << startNode.neighbors[2].xCoord << "," << startNode.neighbors[2].yCoord << endl;
    //std::cout << " down node:" << startNode.neighbors[3].xCoord << "," << startNode.neighbors[3].yCoord << endl;


}

// C:\Users\mikem\source\repos\gameAI_project_one\Project1\data\project1.txt
void testGraph() {
    vector<vector<char>> inputMap;
    string loc;
    cout << "Enter the location of the file:";
    cin >> loc;
    //loc = "project1.txt";
    readMap(loc, inputMap);

    Graph testGraph(inputMap);

    cout << "first Node X : " << testGraph.graph[0][0].xCoord << endl;
    cout << "first Node y : " << testGraph.graph[0][0].yCoord << endl;
    cout << "first Node cost : " << testGraph.graph[0][0].nodeCost << endl;

    //cout << "Fetch neighbor test x: " << testGraph.graph[1].neighbors[0][0] << endl;
    //cout << "Fetch neighbor test y: " << testGraph.graph[1].neighbors[0][1] << endl;

}


//  C:\Users\mikem\source\repos\gameAI_project_one\Project1\data\project1.txt
// Program Entry: 
int main()
{
  
    Test();  //Running the program with testing (no user input)

    //testNode();

    //testGraph();

    return 0;
}
