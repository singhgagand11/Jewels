#ifndef _JEWELS_MODEL_
#define _JEWELS_MODEL_

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <set>
#include <stack>
#include <iostream>
#include "Dir.h"
#include <list>

using namespace std;

class JewelsModel {
  private:
    int** board;
    int boardSize;
    int totalPieces;
    int similarAdjTileLimit;
    void initModel();
    bool isValidPoint(int x, int y);
    void removeTiles(set<pair<int, int>>);
    void setRandPiece(int x, int y);
    set<pair<int, int>> getTopBottomAdjacentTiles(int x, int y);
    set<pair<int, int>> getLeftRightAdjacentTiles(int x, int y);
    set<pair<int,int>> getAdjacentTiles(int x, int y);
    set<pair<int,int>> getValidAdjacentTiles(int x, int y);
    void removeAccessValidTiles(set<pair<int,int>>);
    static const vector<Dir> DIRECTIONS;
    int score;
  public:
    JewelsModel(int totalPices, int boardSize, int similarAdjTileLimit);
    //JewelsModel(int totalPices, int boardSize);
    JewelsModel() {} ;
    ~JewelsModel();
    set<pair<int, int>>  makeMove(int fromX, int fromY, int toX, int toY);
    bool isGameWon();
    int** getBoard();
    int getBoardSize();
    int getScore();
    
    
};
#endif
