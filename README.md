# CS5150 Project One: A-Star

- Demo for the A - Star algorithm in C++ for CS 5150 Game AI at Northeastern University

## Self Reflection:
  - was able to complete the assignment the challenging portions were understanding the correct way to calculate the 
     f,g,h values for each grid node
  - also thinking of how the algorthim could back track, after running into an obstacle took some tinkering to figure out
## Set up:
	- Download program file


## Run and Test Instructions:
    - Commands using CmakeLists.txt, navigate to the main project folder
         - cmake .
         - make
         - ./App
         - enter absolute path of input file 


    - windows: use visual studio debugger to run main.cpp
    - enter the entire path of the input file


- Notes:
  - calculate cost of the new node
  - g = the movement cost to move from the starting point to a given square on the grid, following the path generated to get there.
  - h = the estimated movement cost to move from that given square on the grid to the final destination.This is often referred to as the heuristic,
  - f = sum of g and h

## Resources: 

- https://www.redblobgames.com/pathfinding/a-star/
- https://web.archive.org/web/20171022224528/http://www.policyalmanac.org:80/games/aStarTutorial.htm
- https://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html
