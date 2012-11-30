#include "JewelsController.h"

set<pair<int,int>> JewelsController::handleClick(int x, int y){
   set<pair<int,int>> tilesRemoved = set<pair<int,int>>();
   if (clicks.empty()) {
    if (isValidClick(x, y))
      clicks.push_back(pair<int,int>(x,y));
   }else {
    if (isValidMove(x, y)) {
      pair<int,int> firstClick = clicks.front();
      tilesRemoved = model->makeMove(firstClick.first, firstClick.second,
                                    x, y);
      clicks.clear();
    }
    else {
      clicks.clear();
    };
   };
   return tilesRemoved;
};

bool JewelsController::isValidClick(int x, int y) {
  if ( x >= 0 && x < boardSize &&
       y >= 0 && y < boardSize)
       return true;
  return false;
};
bool JewelsController::isValidMove(int x, int y) {
  if (!clicks.empty()) {
    pair<int,int> firstMove = clicks.front();

    for (vector<Dir>::const_iterator dir = JewelsController::DIRECTIONS.begin();
            dir != JewelsController::DIRECTIONS.end(); ++dir) {
      if (firstMove.first + dir->x == x && 
          firstMove.second + dir->y == y)
          return true;
    }
  }
  return false; 
};

JewelsController::JewelsController(JewelsModel *model) : model(model) {
  boardSize = model->getBoardSize();
};

list<pair<int,int>> JewelsController::getClicks() {
  list<pair<int,int>> clicksList = list<pair<int,int>>();
  
  for (list<pair<int,int> >::iterator click = clicks.begin();
        click != clicks.end(); ++click) {
    clicksList.push_back(pair<int,int>(*click));  
  }; 
  return clicksList;
};    

static const Dir stuff[] = {Dir::NORTH, Dir::SOUTH, Dir::EAST, Dir::WEST};
const vector<Dir> JewelsController::DIRECTIONS = vector<Dir>(stuff, stuff + (sizeof(Dir) * 4));