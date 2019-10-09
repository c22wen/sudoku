#include "cell.h"
#include "game.h"

using namespace std;

// ============================ PRIVATE FUNCTIONS ============================

// Remove n as a possibility
void Cell::removePos(int n){
  for (int i = 0; i < posVal.size(); ++i){
    if (posVal[i] == n){ 
      posVal.erase(posVal.begin() + i); 
      break; 
    }
  }
}


// Remove n as a possibility from all neighbouring cells
void Cell::removePosFromNeighbours(int n){
  for (auto &it : row){
    if(it->getVal() == 0){ it->removePos(n); }
  }
  for (auto &it : col){
    if(it->getVal() == 0){ it->removePos(n); }
  }
  for (auto &it : box){
    if(it->getVal() == 0){ it->removePos(n); }
  }
}


// ============================ SETTERS ============================

// Sets the row to myRow, column to myCol, box to myBox
void Cell::setNeighbours(vector<Cell *> myRow, vector<Cell *> myCol,
                         vector<Cell *> myBox){
  row = myRow;
  col = myCol;
  box = myBox;
}


// Remove all the values of neighbouring cells as a possibility
void Cell::setPossibilities(){
  if (isFixed){
    posVal.clear();
    removePosFromNeighbours(val);
  }
}


// ============================ PRINT FUNCTIONS ============================

void Cell::printPos(){
  cout << "printPos: ";
  for (auto &it : posVal){
    cout << it << " ";
  }
  cout << endl;
}


void Cell::printNPos(){
  for(auto &it : row){
    for(auto &n : it->posVal){ cout << n; }
    cout << " ";
  } 

  for(auto &it : col){
    for(auto &n : it->posVal){ cout << n; } 
    cout << " ";
  } 

  for(auto &it : box){
    for(auto &n : it->posVal){ cout << n; } 
    cout << " ";
  } 
  cout << endl;
}


void Cell::printN(){
    std::cout << "printN: ";
    for(auto &it : row){ std::cout << it->getVal(); }
    std::cout << " ";  
    for(auto &it : col){ std::cout << it->getVal(); }
    std::cout << " ";
    for(auto &it : box){ std::cout << it->getVal(); }
    std::cout << std::endl;
}


// ============================ ITERATE FUNCTION ============================

void Cell::onlyPosInRow(bool fixed){
  bool containsPos = false;
  for(auto &pos : posVal){
    for(auto &it : row){
      if(it == this || it->val != 0) { continue; }
      for(auto &rPos : it->posVal){ // unfilled
        if(pos == rPos){ containsPos = true; break; } // go to next pos
      }
      if (containsPos) { break; }
    } 
    if (!containsPos) {update(pos, fixed);}
  } 
} 


void Cell::onlyPosInCol(bool fixed) {
  bool containsPos = false;
  for(auto &pos : posVal){
    for(auto &it : col){
      if(it == this || it->val != 0) { continue; }
      for(auto &cPos : it->posVal){ // unfilled
        if(pos == cPos){ containsPos = true; break; } // go to next pos
      }
      if (containsPos) { break; }
    } 
    if (!containsPos) {update(pos, fixed);}
  } 
} 


void Cell::onlyPosInBox(bool fixed) {
  bool containsPos = false;
  for(auto &pos : posVal){
    for(auto &it : box){
      if(it == this || it->val != 0){ continue; }
      for(auto &bPos : it->posVal){ // unfilled
        if(pos == bPos){ containsPos = true; break; }  // go to next pos
      }
      if (containsPos) { break; }
    } 
    if (!containsPos) {update(pos, fixed);}
  } 
}


// ============================ UPDATE FUNCTION ============================

// Update the cell value to n
//    If fixed, clear all possible values for the cell
//    Else remove n as a possibility
//    Remove n as a possibility for all nieghbouring cells
//    Change isFixed value to parameter
//    Increase number of changes (to avoid infinite loop)
void Cell::update(int n, bool isfixed) {
  val = n; // FIND N THEN REMOVE IT
  if (isfixed) { posVal.clear();} 
  else { posVal.erase(posVal.begin()); }
  removePosFromNeighbours(n); 
  board->increaseNumChanges();
}


void Cell::resetPos(){ 
	if (val == 0) {
		posVal = {1,2,3,4,5,6,7,8,9};
		for(auto &it : row){ it->removePosFromNeighbours(it->getVal()); }
		for(auto &it : col){ it->removePosFromNeighbours(it->getVal()); }
		for(auto &it : box){ it->removePosFromNeighbours(it->getVal()); }
	}
	if (nextNode != NULL){ nextNode->resetPos();} 
}


bool Cell::checkSum(){
  int rowSum = 0; 
  int boxSum = 0;
  int colSum = 0;
  for(auto &rowCell : row){
    rowSum += rowCell->getVal();
  }
  for(auto &boxCell : box){
    boxSum += boxCell->getVal();
  }
  for(auto &colCell : col){
    colSum += colCell->getVal();
  }
  return (colSum == 45) && (rowSum == 45) && (boxSum == 45);
}
