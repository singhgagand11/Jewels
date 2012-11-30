#ifndef _CONSOLE_VIEW_
#define _CONSOLE_VIEW_

#include "JewelsModel.h"
#include <iostream>

using namespace std;

class ConsoleView {
  private: 
    JewelsModel *model;
    int pieces;
    int size;
    void deleteBoard(JewelsPiece **board, int rowSize);

  public:
    ConsoleView(int, int);
    ~ConsoleView();
    void display();
    void makeMove();
};
#endif
