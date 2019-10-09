#ifndef __GAME__
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Cell; 

class Game {
  // Fields
  int numChanges = 1; // Number of changes each iteration
  std::vector<std::vector<Cell *>> board; 
  std::vector<Cell *> bt; // Vector of cells that are updated in backtracking
  Cell *start; // First cell to backtrack

  // Set-up functions
  void readInSudoku(); // Reads and makes a sudoku
  void addNeighbours(int r, int c); // Sets the neighbours for the cell in row r, and column c

  // Helper functions
  bool containsBT(Cell *c); // Determines if c is in the bt vector
  Cell  *getCell(int row, int col); // Gets the cell in the specified row and column

public:
  Game();
  ~Game();

  // Accessors and Setters
  int getNumChanges() { return numChanges; }
  void increaseNumChanges() { ++numChanges; }
  void resetNumChanges() { numChanges = 0; }  
  
  // Helper functions
  void setupGame(); // Reads in a sudoku, adds all neighbours, and sets up the possibilies  
  void printGame(); // Prints Game; helpful for debugging
 
  // Main functions
  void iterate(bool fixed);
  Cell *setBacktrack();
  bool checkSolved();
  void backtrack();
  void nextGuess(Cell *c);
};

#endif