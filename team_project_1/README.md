##CSCI 104 Team Project Repository

###Student Information
**Developer 1**:
  + Name: Hao Cui
  + USC Email: hcui@usc.edu
  + USC ID: 1454367516

**Developer 2**:
  + Name: Kimberlee Holland
  + USC Email: kimberch@usc.edu
  + USC ID: 9876543210

###Complie Instruction

make -f Makefile.crawler
use the above line to compile crawler.exe, the exe will be in the repo folder

qmake
make
use the above two lines to compile team_project_23,which is the main
boodle.cpp is the main

###Design 
For crawler:
I use stack to implement DFS, only add text name to output index when it's being explored. When parsing, push un-seen links into stack and break the parsing to ensure DFS. Only pop items from stack when the found flag is false, so this will make sure all the links being explored.

For mergesort:
It's in lib

For pagerank:
In the searchWindow.cpp(mainwindow), I extend the searching results to incoming and outgoing links within one level.
In the MySearchList.h(the scroll menu class), I declare a struct to deal with rank page
It has a rank value member and also a value received member, and also a deque to store adjaceny.
In the MySearchList.cpp, in the updateList function, I first build the adjaceny list into a deque. During the iterative loops, all the distributed weight is stored in the value received member, then replace the current rank value with the value received and reset the value received to 0.



