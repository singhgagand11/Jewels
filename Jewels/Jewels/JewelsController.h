#ifndef _JEWELS_CONTROLLER_
#define _JEWELS_CONTROLLER_

#include "JewelsModel.h"
#include <queue>
#include <list>

class JewelsController {
  public:
    set<pair<int,int>> handleClick(int x, int y);
    JewelsController(JewelsModel *model);
    list<pair<int,int>> getClicks();  
    bool isValidClick(int x, int y);  
  private:
    JewelsModel *model;
    list<pair<int, int>> clicks;
    int boardSize;
    bool isValidMove(int x, int y);
    static const vector<Dir> DIRECTIONS;
    
};
#endif