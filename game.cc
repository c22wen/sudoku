
#include "game.h"
#include "cell.h"
using namespace std;

Game::Game() {}


Game::~Game() {
  for (auto &out : board) {
    for (auto &in : out) {
      delete in;
    }
  }
}


// ======================================================= SET UP

// Adds all the neighbours for the Cell in row r, col c
void Game::addNeighbours(int r, int c) {
  vector<Cell *> myCol; // Setting up col
  for (int j = 0; j < board.size(); ++j) {
    myCol.push_back(board[j][c]);
  }

  vector<Cell *> myBox; // Setting up box
  int centerRow;
  int centerCol;
  // Find centerRow
  if ((0 <= r) && (r <= 2)) { centerRow = 1;
  } else if (r <= 5) {  centerRow = 4;
  } else { centerRow = 7; }
  // Find centerCol
  if ((0 <= c) && (c <= 2)) { centerCol = 1;
  } else if (c <= 5) { centerCol = 4;
  } else { centerCol = 7; }

  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      myBox.push_back(board[i + centerRow][j + centerCol]);
    }
  }
  board[r][c]->setNeighbours(board[r], myCol, myBox);
}


// Reads and makes a sudoku
void Game::readInSudoku() {
  int n;
  string s;

  // Reading in Sudoku board
  vector<vector<Cell *>> myBoard;
  for (int i = 0; i < 9; ++i) {
    vector<Cell *> row;
    for (int j = 0; j < 9; ++j) {
      cin >> s;
      istringstream iss{s};
      if (iss.str() == "_") { // unfilled slot
        Cell *c = new Cell{false, 0};//, i, j};
        row.push_back(c);
      } else if ((iss >> n) && (0 < n) && (n <= 9)) { // filled
        Cell *c = new Cell{true, n};//, i, j};
        row.push_back(c);
      } else {
        cout << "Input Error" << endl; // throw/catch exception
      }
    }
    myBoard.push_back(row);
  }
  board = myBoard;
}


// Reads in a sudoku, adds all neighbours, and sets up the possibilies
void Game::setupGame() {
  readInSudoku();
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      addNeighbours(i, j);
      board[i][j]->setPossibilities();
      board[i][j]->setBoard(this);
    }
  }
}


Cell *Game::getCell(int row, int col) { return board[row][col]; }


void Game::printGame() {
  cout << "---------------------" << endl;
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      (board[i][j]->getVal() == 0) ? cout << "_"
                                   : cout << board[i][j]->getVal();
      ((j == 2) || (j == 5)) ? cout << "\t" : cout << " ";
    }
    if ((i == 2) || (i == 5)) { cout << endl; }
    cout << endl;
  }
  cout << "---------------------" << endl;
}


void Game::iterate(bool fixed) {
  for(auto &out : board){
    for(auto &in : out) {
      in->onlyPosInRow(fixed);
      in->onlyPosInCol(fixed);
      in->onlyPosInBox(fixed);
      if(in->getNumPos() == 1) {   
        in->update(in->getFirstPos(), fixed); 
      }
    }
  }
}


Cell * Game::setBacktrack() { 
  Cell *prev = NULL;
  Cell *start = NULL;
  for(auto &r : this->board) {
    for (auto &c : r) {
      if(c->getIsFixed()) { continue; }
      if(prev == NULL) { prev = c; start = c; }
      c->addPrev(prev); // set the nextNode of previous
      prev->addNext(c); // set prevNode of current cell
      prev = c;
    }
  }
  this->start = start;
  return start;
}


bool Game::checkSolved() {
  return getCell(0,0)->checkSum() && getCell(1,3)->checkSum() && getCell(2,6)->checkSum() 
      && getCell(3,1)->checkSum()  && getCell(4,4)->checkSum()  && getCell(5,7)->checkSum()  
      && getCell(6,2)->checkSum()  && getCell(7,5)->checkSum()  && getCell(8,8)->checkSum();                      
}


  bool Game::containsBT(Cell *c) {
    for (auto &curCell : bt) {
      if (curCell == c) { return true; }
    }
  return false;
  }

  void Game::backtrack(){
  	Cell *last = bt.back();
  	if (last->getNumPos() > 0) {
  		last->update(last->getFirstPos(), false);
  		start->resetPos();
  	} else {
  		last->resetVal();
  		bt.pop_back();
  		backtrack();
  	}
  }

  void Game::nextGuess(Cell *c){
      c->update(c->getFirstPos(), false);
      bt.push_back(c);  
  }
