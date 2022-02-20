# CS5150 Project One: A-Star

- Demo for the A-Star algorithm in C++ for CS 5150 Game AI at Northeastern University

## Self Reflection:
 - Completed all core parts of the assignment. Creating a custom hash function to use with an unordered grid was challenging, as c++ only supports primitive types with their containers. I did not attempt to create a path smoothing solution into my program.

### Features:
  - Diagonal movement
  - Weighted nodes, including 0
  - User input for manhattan and linear heuristics
  - User input for output map type, showing expanded, all, or standard modes

## Set up:
	- Download program files on your machine
    - Navigate to the downloaded directory
    - Mac, have cmake installed
    - Windows, have visual studio or cmake/cmake gui installed

## Run and Test Instructions:
    - Mac:
    - In your command line program of choice, navigate to the main project folder, utilize the cmakelists.txt to compile the project
         - cmake .
         - make
         - ./App  (the executable is called "App")
         - enter absolute path of input file when prompted

    - Windows:
    - Using visual studio windows compiler:
    - open the project folder to windows visual studio
    - run and build project using the visual studio debugger to run main.cpp
    - enter the entire path of the input file when prompted

    - Using cmake or cmake gui:
    - In your command line program of choice, build the source files with the given cmakelists.txt file
    - run the program with the executable called "./App"
    - enter the entire path of the input file when prompted
    

## Example Graphs:
    - Graphs are made up of nxn characters in a text file
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

  
- Notes:
  - Calculate cost of the new node:
  - g = the movement cost to move from the starting point to a given square on the grid, following the path generated to get there.
  - h = the estimated movement cost to move from that given square on the grid to the final destination.This is often referred to as the heuristic,
  - f = g + nodeCost * h

## Resources: 

- https://www.redblobgames.com/pathfinding/a-star/
- https://web.archive.org/web/20171022224528/http://www.policyalmanac.org:80/games/aStarTutorial.htm
- https://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html
