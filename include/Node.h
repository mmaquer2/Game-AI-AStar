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


    Node(int x, int y);

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

    array<int,2> parentLocation;

	vector<std::array<int, 2>> neighbors;
	vector<Node> cameFrom;

	array<int ,2> getLocation();
	int calculateNeighbors();
	vector<std::array<int, 2>> getNeighbors();

	int getH();
	int getG();
	int getF();

	int setH(int newH);
	int setG(int newG);
	int setF(int newF);

    private:




};

#endif