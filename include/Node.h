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

    Node(Node **pNode);

    Node(array<int, 2> *pArray);

    Node(Node *pNode);

    hash<int> hash;

    int nodeCost = 0;
	int xCoord = 0;
	int yCoord = 0;
	bool passable;
	bool discovered;
    Node* parentNode;
	bool expanded;
	int g = 0;
	int h = 0;
	int f = 0;

    array<int,2> parentLocation;

	vector<std::array<int, 2>> neighbors;
	vector<Node> cameFrom;

	array<int ,2> getLocation();
	int calculateNeighbors();


    private:




};

#endif