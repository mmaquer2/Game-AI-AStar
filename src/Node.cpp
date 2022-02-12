#include<iostream>
#include<vector>
#include "../include/Node.h"
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

using namespace std;


	//class constructor
Node::Node(int x, int y) {
		xCoord = x;
		yCoord = y;
		passable = false;
		expanded = false;
		discovered = false;
		closed = false;
	
};

	//getter function to return the x,y values of the node
	array<int ,2> Node::getLocation() {

		std::array<int ,2> cords;
		cords[0] = xCoord;
		cords[1] = yCoord;

		return cords;
	}

	//helper function to obtain the neighbor x,y of the node object
	int Node::calculateNeighbors() {

	
		//cardinal direction neighbors:
		std::array<int,2> right;
		std::array<int, 2> left;
		std::array<int, 2> up;
		std::array<int, 2> down;

		right[0] = xCoord + 1;
		right[1] = yCoord;

		left[0] = xCoord - 1;
		left[1] = yCoord;

		up[0] = xCoord;
		up[1] = yCoord + 1;

		down[0] = xCoord;
		down[1] = yCoord - 1;


		neighbors.push_back(right);
		neighbors.push_back(left);
		neighbors.push_back(up);
		neighbors.push_back(down);
		
		std::cout << "added new neighbors" << endl;
		
		return 0;
	}



	vector<std::array<int, 2>> Node::getNeighbors() {

		return neighbors;
	}

	int Node::getF() {
		return f;
	}

	int Node::getH() {
		return h;
	}

	int Node::getG() {

		return g;
	}


	int Node::setH(int newH){
		h = newH;

		return h;
	};

	int Node::setG(int newG){
		
		g = newG;

		return g;
	};

	int Node::setF(int newF){
	
		f = newF;
		return f;
	};

