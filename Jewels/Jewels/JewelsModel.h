#ifndef _JEWELS_MODEL_
#define _JEWELS_MODEL_

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <set>
#include <stack>
#include <iostream>
#include "Dir.h"
#include "JewelsPiece.h"
#include "JewelsView.h"
#include <list>

using namespace std;

class JewelsModel {
  private:
    JewelsPiece** board;
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
    JewelsPiece** createBoard();
    static const vector<Dir> DIRECTIONS;
    int score;
    void (*repaint)();
    bool viewSet;
  public:
    JewelsModel(int totalPices, int boardSize, int similarAdjTileLimit);
    //JewelsModel(int totalPices, int boardSize);
    JewelsModel() {} ;
    ~JewelsModel();
    set<pair<int, int>>  makeMove(int fromX, int fromY, int toX, int toY);
    bool isGameWon();
    JewelsPiece** getBoard();
    int getBoardSize();
    int getScore();
    void selectPiece(int x, int y);
    void deselectPiece(int x, int y);
    void setView(void (* repaint)());
    
    
};
#endif
