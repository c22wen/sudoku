#ifndef __CELL__ 
#include <iostream>
#include <sstream>
#include <string>
#include <vector> 

class Game;

class Cell {
  bool isFixed;
  int val;
  std::vector<Cell *> row;
  std::vector<Cell *> col;
  std::vector<Cell *> box;
  std::vector<int> posVal = {1,2,3,4,5,6,7,8,9};
  Game *board;
  Cell *prevNode; // previous unsolved cell
  Cell *nextNode; // next unsolved cell

  // Private functiosn
  void removePos(int i); // Remove i from the vectors of possibilities
  void removePosFromNeighbours(int i); // Remove n if it's a possibility in neighbouring cells

public:
  Cell(bool isFixed, int val) : isFixed{isFixed}, val{val} {} 


  // Accessors
  bool getIsFixed() { return isFixed; }
  int getVal() { return val; }
  int getNumPos() { return posVal.size(); }
  int getFirstPos() { return posVal[0]; }
  Cell *getNextNode() { return nextNode; }

  // Setters
  void setNeighbours(std::vector<Cell *> myRow, std::vector<Cell *> myCol,
                     std::vector<Cell *> myBox);
  void setPossibilities(); // Remove all the values of neighbouring cells as a possibility
  void setBoard(Game * const g) { board = g; }
  void addPrev(Cell *c) { prevNode = c; } // Used to set-up backtracking
  void addNext(Cell *c) { nextNode = c; } // Used to set-up backtracking
  void resetVal() { val = 0; }

  // Printing functions; helpful for debugging
  void printPos();
  void printN();
  void printNPos();

  // If cell is the only possibility for n in the row/column/box
  void onlyPosInRow(bool fixed);
  void onlyPosInCol(bool fixed);
  void onlyPosInBox(bool fixed);

  // Update the cell value to n
  //    If fixed, clear all possible values for the cell
  //    Else remove n as a possibility
  //    Remove n as a possibility for all nieghbouring cells
  //    Change isFixed value to parameter
  //    Increase number of changes (to avoid infinite loop)
  void update(int n, bool fixed);
  
  void resetPos(); // Reset all possibilities affected by backtrack
  bool checkSum(); // Check the sum of the row/column/box 
};

#endif