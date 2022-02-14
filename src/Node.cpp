
#include "../include/Node.h"
#include <array>

using namespace std;

//class constructor
Node::Node(int x, int y) {
		xCoord = x;
		yCoord = y;


};

	//getter function to return the x,y values of the node
	array<int ,2> Node::getLocation() {
		std::array<int ,2> cords;
		cords[0] = xCoord;
		cords[1] = yCoord;
        parentNode = nullptr;

		return cords;
	}

	//helper function to obtain the neighbor x,y of the node object
	int Node::calculateNeighbors() {

		//cardinal direction neighbors:
		std::array<int,2> right;
		std::array<int, 2> left;
		std::array<int, 2> up;
		std::array<int, 2> down;

        //diagonal direction neighbors
        std::array<int,2> topRight;
        std::array<int, 2> topLeft;
        std::array<int, 2> bottomRight;
        std::array<int, 2> bottomLeft;

        topRight[0] = xCoord + 1;
        topRight[1] = yCoord + 1;

        bottomRight[0] = xCoord - 1;
        bottomRight[1] = yCoord + 1;

        topLeft[0] = xCoord + 1;
        topLeft[1] = yCoord - 1;

		bottomLeft[0] = xCoord - 1;
		bottomLeft[1] = yCoord - 1;

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
        neighbors.push_back(topRight);
        neighbors.push_back(topLeft);
        neighbors.push_back(bottomLeft);
        neighbors.push_back(bottomRight);
		
		//std::cout << "added new neighbors" << endl;
		
		return 0;
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
	}

Node::Node(Node **pNode) {

}

Node::Node(array<int, 2> *pArray) {

}



