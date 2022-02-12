
#ifndef GRAPH_HPP 
#define GRAPH_HPP

#include "Node.h"
#include<vector>

using namespace std;



class Graph {

	public:
	
	vector<vector<Node>> graph;

	Graph(std::vector<std::vector<char>>& PathMap);
	void calculateNeighbors();
	void findNodeNeighbors();




};

#endif