#ifndef NODE_HPP 
#define NODE_HPP

#include<iostream>
#include<vector>
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

using namespace std;
class Node {

public:

	int nodeCost = 0;
	int xCoord = 0;
	int yCoord = 0;
	bool passable;
	bool discovered;
	bool expanded;
	bool closed;

	int g = 0;
	int h = 0;
	int f = 0;

	vector<std::array<int, 2>> neighbors;
	vector<Node> cameFrom;

	Node(int x, int y);

	array<int ,2> getLocation();
	int calculateNeighbors();
	vector<std::array<int, 2>> getNeighbors();

	int getH();
	int getG();
	int getF();

	int setH(int newH);
	int setG(int newG);
	int setF(int newF);


};

#endif