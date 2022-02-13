#include "../include/Graph.h"
#include <vector>

using namespace std;

Graph::Graph(std::vector<std::vector<char>>& input) {

	for (int i = 0; i < input.size(); i++) {

		vector<Node> rowArr; //temp row vector
		
		for (int j = 0; j < input[i].size(); j++) {

			char temp = input[i][j];
			Node tempNode(i, j);
			// if the tempNode is the value of X it's not a passable location on the map
			if (temp == 'X') {
				tempNode.passable = false;
				tempNode.nodeCost = -1;
			} 
			//if the node is passable set bool to true, and record the weight of the node cost
			else {
				tempNode.passable = true;
                tempNode.discovered= false;
                tempNode.expanded = false;
				int tempCost = (int)temp - 48; //due to unicode values have to subtract 48 to get the correct int value
				tempNode.nodeCost = tempCost;

			}

			//std::cout << temp << std::endl;
			std::cout << "new node added from  " << i << " , " << j << " cost: " << tempNode.nodeCost << " passable: " << tempNode.passable << endl;
			
			//add node to the graph vector
			
			rowArr.push_back(tempNode); //add the tempNode to the current row
		}

		graph.push_back(rowArr); //push the current row back onto the graph
	}


    //set the height and width of the graph to check boundries
    //height = 4;
    //width = 4;

    height = graph.size() -1 ;
    width = graph[0].size()-1;

    cout << "graph height: " << height << endl;
    cout << "graph width: " << width << endl;

    findNodeNeighbors(); //find all neighbor nodes in the graph


}


void Graph::findNodeNeighbors() {

	//have each node calculate its own neighbors in the graph
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++) {

			graph[i][j].calculateNeighbors();

		}

	}

}