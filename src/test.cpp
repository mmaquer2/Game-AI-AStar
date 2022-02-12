#include <chrono>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>
#include "Project1.h"
#include "Node.h"
#include "Graph.h"


using namespace std;



//  C:\Users\mikem\source\repos\gameAI_project_one\Project1\data\project1.txt
void PlanPath(const vector<vector<char>>& inputMap, int start[2], int destination[2], eMode mode, eHeuristic heuristic , Graph nodeGraph )
{
    // Start the timer
    using namespace chrono;
    steady_clock::time_point clock_begin = steady_clock::now();


    vector<Node>gScore;
    vector<Node>fScore;
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
   bool pathDiscovred = false; // set discovered path boolean to false

    while (openSet.size() > 0) {

       Node currentNode = openSet.front(); //get node at front of openList
       currentNode.expanded = true; // set the current node expnaded flag to true
       currentNode.discovered = true; // set the temp node to discovered flag to true
       openSet.pop_back(); //remove the top element just recieved 

       closedSet.push_back(currentNode); //insert current node into the closedSet

       cout << "current node cost: " << currentNode.nodeCost << endl;


       //check if destination has been reached  
       if (currentNode.getLocation() == endNode.getLocation() ) {            
           pathDiscovred = true; //the closed set now contains the final path from start to finish
            break;
       }

       std::cout << "looking at neighbors --->" << endl;
     
       for (int i = 0; i < currentNode.neighbors.size(); ++i) {

           array<int, 2> tempCoors = currentNode.neighbors[i]; // get the coordinates of the neighbor
           
           cout << "neighbor coordinates" << tempCoors[0] << tempCoors[1] << endl;
           
           //check if the neighbor is valid within the graph:
           //TO DO: 
           //also need to check the width of the neighbors as well
           if ((tempCoors[0] >= 0) && (tempCoors[1] >= 0)  ) {

               
               Node tempNeighbor = nodeGraph.graph[tempCoors[0]][tempCoors[1]]; //get the current neighbor node

               tempNeighbor.discovered = true; //set the neighbornode to discovered 


                //calculate cost of the new node

               // g = the movement cost to move from the starting point to a given square on the grid, following the path generated to get there. 
               // h = the estimated movement cost to move from that given square on the grid to the final destination.This is often referred to as the heuristic,
               // f = sum of g and h

                //TODO:
               // How to properly calculate the values of f,g,h

               int tentativeCost = currentNode.g + (currentNode.g + tempNeighbor.g);

               cout << "cost for add this neighbor node:  " << tentativeCost << endl;

               bool neighborInOpen = false;

               //check if the node is not in the openSet
              // for (int i = 0; i < openSet.size(); i++) {
                  // Node temp = openSet[i];
                  // if (temp == tempNeighbor) {
                    //   neighborInOpen = true;
                  // }

               //}

               // if this path to the neighbor is better than the previous path
               if ((tentativeCost < tempNeighbor.g) || neighborInOpen ) {

                   cout << "accepting the tentative cost of the new neighbor node " << endl;
                   
                   //cameFrom[neighbor] == current;
                   //currentNeighbors[i].cameFrom = currentNode;
                
                   tempNeighbor.g = tentativeCost;
                   //tempNeighbor.h = tentativeCost + h(tempNeighbor);

                   //TODO: how to properly use the find function for a Node object
                 
                     openSet.push_back(tempNeighbor);
                  

               }
               


           }

       } 

    }

    //if open set is empty and goal was never reached == this was a failure cannot find an open path


    // Stop the timer
    steady_clock::time_point clock_end = steady_clock::now();
    steady_clock::duration time_span = clock_end - clock_begin;
    double seconds = double(time_span.count()) * steady_clock::period::num / steady_clock::period::den;

    std::cout << endl;
    std::cout << "It took " << seconds << " seconds.";
    std::cout << endl;

    //if a path cannot be found... return -1, report notice path not found...
    //if (pathDiscovred == false) {
        
            //cout << "A path could not be found" << endl;

    //}

    //else {

        


    //}

    // Annotate & print the output map
    //vector<vector<char>> outputMap = inputMap;



    // YOUR CODE RESUMES HERE
    // Annotate the output map with your path, along with expanded nodes and fringe nodes 
    // (if the mode calls for them)

    //create a new output file
    string outputPath = "outputPath.txt";
    //s = start node
    //d = destination node
    //+ = path node
    //t = touched/discovered noe
    //e = expnaded nodes

    //iterate through the examined/modified inputMap and 


    //Annotate the map based on the mode selected 


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





//Heuristic Functions


int MhtnFunction() {


    return 0;
}


int LinearFunction() {


    return 0;
}

//Mode Functions

int StandardFunction() {


    return 0;
}


int ExpandFunction() {

    return 0;
}

int AllFunction() {

    return 0;
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
    end[0] = 2;
    end[1] = 2;

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
