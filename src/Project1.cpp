
//#include <chrono>
//#include <unordered_map>
//#include <queue>
//#include <vector>
//#include <algorithm>
//#include "Project1.h"
//#include "Node.h"
//#include "Graph.h"



using namespace std;

/*
void PlanPath(const vector<vector<char>>& inputMap, int start[2], int destination[2], eMode mode, eHeuristic heuristic)
{   
    // Start the timer
    using namespace chrono;
    steady_clock::time_point clock_begin = steady_clock::now();
    
    Node startNode(start[0], start[1]); //create start node 
    Node destinationNode(destination[0], destination[1]); //create destination node

    vector<Node> cameFrom;
    //vector<Node, int> totalCost;
    vector<Node> openSet; //container for tracking currently exmained code

     
    //cameFrom[startNode] = startNode;
    //totalCost[startNode] = 0;

    //insert start node to open container
    openSet.push_back(startNode);
    bool pathDiscovred = false;
    
    while (openSet.size() > 0) {

       Node currentNode = openSet.front(); //get node at front of openList
      
       
        //check if destination has been reached  
       if ( startNode.getLocation() == currentNode.getLocation()  ) {
           pathDiscovred = true;
           //reconstruct path, cameFrom to currentNode
            break;
       }

       
       
       openSet.pop_back(); //remove the top element just recieved 
       vector<std::array<int, 2>> currentNeighbors = currentNode.getNeighbors();

       for (int i = 0; i < currentNeighbors.size(); ++i) {
         
               //calculate cost of the new node
               int new_cost = currentNode.g + currentNode.f + currentNeighbors[i].f;

               // if this path to the neighbor is better than the previous path
               if (new_cost < currentNeighbors[i].g) {

                   //cameFrom[neighbor] == current;
                   //currentNeighbors[i].cameFrom = currentNode;
                   //gScore[neighbor] == tentaive g socre + h(neighbor)
                  // currentNeighbors[i].g = new_cost;
                   //currentNeighbors[i].f = new_cost + h(currentNeighbors[i];


                   //check if the currentneighbor[i] is in the openSet
                   if (std::find(openSet.begin(), openSet.end(), currentNeighbors[i]) != openSet.end()) {
                      
                       //openSet.push_back(currentNeighbors[i]);
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
    if (pathDiscovred == false) {


    }

    else {


    }

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



// eMode { Standard, Expanded, All };
// eHeuristic { StraightLine, Manhattan };
// path of the input txt file:  C:\Users\mikem\OneDrive\Desktop\Project1\data\project1.txt

int Start() {

    vector<vector<char>> inputMap;
    string loc;
    string modeType, heuristicType;
    int start[2], end[2];

    cout << "Enter the location of the file:";
    cin >> loc;

    readMap(loc, inputMap);

    cout << endl;
    cout << "the input map is:\n";
    PrintMap(inputMap);

    cout << endl;
    cout << "Enter the mode:";
    cin >> modeType;

    eMode mode = convertMode(modeType);

    cout << endl;
    cout << "Enter the heuristic:";
    cin >> heuristicType;
    heuristicType = "Manhattan";

    eHeuristic heuristic = convertHeuristic(heuristicType);

    cout << endl;
    cout << "Start coordinate:";
    cin >> start[0];
    cout << "Start y coordinate:";
    cin >> start[1];



    cout << endl;
    cout << "End x coordinate:";
    cin >> end[0];
    cout << "End y coordinate:";
    cin >> end[1];


   PlanPath(inputMap, start, end, mode, heuristic);
    
    return 0;
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

// Program Entry: 
//int main()
//{
   // Start(); 
//}

*/