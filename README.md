# CS5150 Project One: A-Star

- Demo for the A - Star algorithm in C++ for CS 5150 Game AI at Northeastern University

## Self Reflection:
 - Completed all core parts of the assignment, creating a custom hash function to use with an unordered grid was challenging, as c++ only supports primitive types with their containers.

## Features:
  - Diagonal movement
  - Weighted nodes, including 0
  - User input for manhattan and linear heuristic
  - User input for output map, expanded, all, or standard modes

## Set up:
	- Download program files on your machine
    - Navigate to the downloaded diretory

## Run and Test Instructions:
    - Mac:
    - Commands using CmakeLists.txt, navigate to the main project folder
         - cmake .
         - make
         - ./App
         - enter absolute path of input file when prompted

    -Windows:
    - upload files to windows visual studio
    - run and build project using the visual studio debugger to run main.cpp
    - enter the entire path of the input file when prompted

## Example Graphs:
    - graphs are made up of nxn characters in a text file
    - each node can have a weight int 0 to 9 
    - an X char marks an inpassabile node

    - Example Graphs:
    - 111   
      111
      111

    - 1151
      1XX1
      X151
      1111
    
    - 
  
- Notes:
  - calculate cost of the new node
  - g = the movement cost to move from the starting point to a given square on the grid, following the path generated to get there.
  - h = the estimated movement cost to move from that given square on the grid to the final destination.This is often referred to as the heuristic,
  - f = g + nodeCost * h

## Resources: 

- https://www.redblobgames.com/pathfinding/a-star/
- https://web.archive.org/web/20171022224528/http://www.policyalmanac.org:80/games/aStarTutorial.htm
- https://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html
