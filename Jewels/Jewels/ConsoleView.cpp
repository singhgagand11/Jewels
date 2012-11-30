#include "ConsoleView.h"



ConsoleView::ConsoleView(int pieces, int size) : pieces(pieces), size(size) {
  ConsoleView::model = new JewelsModel(pieces, size, 2);

  while (!model->isGameWon()){
    display();
    makeMove();
  }
};

void ConsoleView::makeMove() {
  int fX, fY, tX, tY;
  cout << "Where you want to move from (x, y) : ";
  cin >> fX >> fY;

  cout << "Where you want to move to (x, y) : ";
  cin >> tX >> tY;

  model->makeMove(fX, fY, tX, tY);
};

ConsoleView::~ConsoleView() {
  //delete model;
};

void ConsoleView::display() {
  JewelsPiece **board = ConsoleView::model->getBoard();
  cout << "  ";
 
  for(int row = 0; row < size; row++)
    cout << row << " ";
  cout << endl;
  cout << "__";
  for(int row = 0; row < size; row++)
    cout << "__";
  cout << endl;

  for (int row = 0; row < size; row++) {
  cout << row << "|";
    for (int col = 0; col < size; col++) {
      cout << board[row][col].getPiece() << " ";
    } 
    cout << endl;
  }
  
  deleteBoard(board, size);
};

void ConsoleView::deleteBoard(JewelsPiece **board, int rowSize) {
  //FOR each column 
  for (int row = 0; row < rowSize; row++) {
    //delete the ptr at that column
    delete[] board[row];
  }
  //delete the ptr to board
  delete[] board;
};
