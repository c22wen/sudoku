#include "cell.h"
#include "game.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() { 
  try {
    Game myGame;
    myGame.setupGame(); // Read in sudoku, set it up
    myGame.printGame(); // Print sudoku
    
    // Backtracking portion
    // Unsolved cells are a linked list
    Cell *start = myGame.setBacktrack();
    while(!myGame.checkSolved()) {
      Cell *btCell = start;
      int lowestNumPos = 10;
      Cell *curNode = start;

      // Find the cell with the lowest number of possibilities
      while(curNode != NULL) {
        if(curNode->getVal() < lowestNumPos && curNode->getVal() == 0) {
          btCell = curNode;
          lowestNumPos = curNode->getNumPos();
        }
        curNode = curNode->getNextNode();
      }

      // Guess its first possibility
      if(lowestNumPos != 0 && lowestNumPos != 10) { 
        myGame.nextGuess(btCell);
      } else  { // Out of possibilities, backtrack
        myGame.backtrack();
      }
    }
    myGame.printGame();
  } catch (...) { cout << "Invalid Sudoku puzzle" << endl; }
}

