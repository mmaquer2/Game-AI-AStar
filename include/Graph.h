
#ifndef GRAPH_HPP 
#define GRAPH_HPP

#include "Node.h"
#include<vector>

using namespace std;



class Graph {

	public:
	
	vector<vector<Node>> graph;
    int width;
    int height;

	Graph(std::vector<std::vector<char>>& PathMap);

	void findNodeNeighbors();
    void calculateHValues(string hType, int end[2]);
    int HeuristicCalc(string hType, Node temp, int end[2]);



};

#endif