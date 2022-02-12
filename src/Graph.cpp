#include "../include/Graph.h"
#include <vector>

using namespace std;

Graph::Graph(std::vector<std::vector<char>>& input) {

	for (int i = 0; i < input.size(); i++) {

		vector<Node> rowArr;
		
		for (int j = 0; j < input[i].size(); j++) {

			char temp = input[i][j];
			Node tempNode(i, j);
			// if the tempNode is the value of X it's not passable location of the map
			if (temp == 'X') {
				tempNode.passable = false;
				tempNode.nodeCost = -1;
			} 
			//if the node is passable set bool to true, and record the weight of the node Cost
			else {
				tempNode.passable = true;
				int tempCost = (int)temp - 48;
				tempNode.nodeCost = tempCost;

			}

			std::cout << temp << std::endl;
			std::cout << "new node added from  " << i << " , " << j << " cost: " << tempNode.nodeCost << " passable: " << tempNode.passable << endl;
			
			//add node to the graph vector
			
			rowArr.push_back(tempNode); //add the tempNode to the current row
		}

		graph.push_back(rowArr); //push the current row back onto the graph


	}

	

	findNodeNeighbors();


}



void Graph::calculateNeighbors() {
	//for every node in the graph, assign the reference to the node location in the graph vector

	//as the neighbors for that node, in order to later reference their cost, f,g, and h values

	//get the indexes of the neighbors

	//for those indexes, a reference to that assigned to the resepective 



}




void Graph::findNodeNeighbors() {

	//have each node calculate its own neighbors in the graph
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++) {

			graph[i][j].calculateNeighbors();

		}


		
	}

}