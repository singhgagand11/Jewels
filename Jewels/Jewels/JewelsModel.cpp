#include "JewelsModel.h"

JewelsModel::JewelsModel(int totalPieces, const int boardSize, int similarAdjTileLimit):boardSize(boardSize), 
totalPieces(totalPieces), similarAdjTileLimit(similarAdjTileLimit), score(0) {

  //SET board to boardSize ptr of int 
  board = new JewelsPiece* [boardSize];
  //FOR each column in boardSize
  for (int col = 0; col < boardSize; col++) {
    //set the the ptr to current board column to array of boardSize integers
    board[col] = new JewelsPiece[boardSize];
  };
  //seed the random # generator  
  srand(1);
  //initilize the board with random pieces
  initModel();
};

void JewelsModel::initModel() {
/**
  //FOR each row in the board
  for (int row = 0; row < boardSize; row++) {
    //FOR each col in the board
    for (int col = 0; col < boardSize; col++) {
      //SET random piece to the current board position
      board[row][col] = -1;
    }
  }
  **/
  //FOR each row in the board
  for (int row = 0; row < boardSize; row++) {
    //FOR each col in the board
    for (int col = 0; col < boardSize; col++) {
      //SET random piece to the current board position
      setRandPiece(row, col);
    }
  }
};

void JewelsModel::setRandPiece(int x, int y) {
 
  board[x][y].setIsSelected(false);
  board[x][y].setIsVisible(true);
  board[x][y].setToRemove(false);
  int ran = rand() % totalPieces;
  board[x][y].setPiece(ran);
  while ( (getLeftRightAdjacentTiles(x, y).size() > similarAdjTileLimit ) ||
          (getTopBottomAdjacentTiles(x, y).size() > similarAdjTileLimit)) {
    board[x][y].setPiece((board[x][y].getPiece() + 1) % totalPieces);
    if (board[x][y].getPiece() == ran) {
      printf("RAND GENERATOR ERROR, NO VALID PIECE TO SET");
      break;
    }
  }
};

JewelsModel::~JewelsModel() {
  //FOR each column 
  for (int col = 0; col < boardSize; col++) {
    //delete the ptr at that column
    delete[] board[col];
  }
  //delete the ptr to board
  delete[] board;
};

set<pair<int, int>> JewelsModel::makeMove(int fromX, int fromY, int toX, int toY) {
  set<pair<int, int>> adjacentTiles = set<pair<int,int>>();
  //IF the two points are within the board
  if (isValidPoint(fromX, fromY) && isValidPoint(toX, toY)) {
    //save the piece and swap the two pieces
    int from = board[fromX][fromY].getPiece();
    int to = board[toX][toY].getPiece();
    board[fromX][fromY].setPiece(to);
    board[toX][toY].setPiece(from);    
    adjacentTiles = getValidAdjacentTiles(fromX, fromY);
      
    //if the two pieces are different
    if (from != to) {
      
      //find the all the similiar adjacent tiles for the second piece
      set<pair<int,int>> validToAdjacentTiles = getAdjacentTiles(toX, toY);
      adjacentTiles.insert(validToAdjacentTiles.begin(), validToAdjacentTiles.end());
    }
    
    //IF the set of adjacent tiles is not empty
    if (!adjacentTiles.empty()) {
      //remove the tiles
      removeTiles(adjacentTiles);
    }
    //else swap the pieces back
    else {
      board[fromX][fromY].setPiece(from);
      board[toX][toY].setPiece(to);
    }
  };   
  
  removeAccessValidTiles(adjacentTiles); 
  return adjacentTiles;
};

void JewelsModel::removeAccessValidTiles(set<pair<int,int>> removedTiles) {
  list<pair<int,int>> tilesToCheck = list<pair<int,int>>(removedTiles.begin(), removedTiles.end());
  set<pair<int,int>> tilesToCheckSet = set<pair<int,int>> (removedTiles.begin(), removedTiles.end());
  while (!tilesToCheck.empty()) {
    pair<int,int> tile = tilesToCheck.front();
    tilesToCheck.pop_front();
    tilesToCheckSet.erase(tile);

    set<pair<int,int>> validToAdjacentTiles = getAdjacentTiles(tile.first, tile.second);
    removeTiles(validToAdjacentTiles);
    if (validToAdjacentTiles.empty() && tile.first > 0) {
      tile.first--;
      if (tilesToCheckSet.count(tile) == 0) {
        tilesToCheck.push_back(tile);
        tilesToCheckSet.insert(tile);
      }
    };

    
    int validToAdjSize = validToAdjacentTiles.size();
    for (set<pair<int,int> >::iterator validAdjTile = validToAdjacentTiles.begin(); 
          validAdjTile != validToAdjacentTiles.end(); ++validAdjTile) {
      if ( tilesToCheckSet.count(*validAdjTile) == 0) {
        tilesToCheck.push_back(*validAdjTile);
        tilesToCheckSet.insert(*validAdjTile);
      }
    }
    
  } 
};

void JewelsModel::removeTiles(set<pair<int, int>> tiles) {

  for(set<pair<int,int> >::iterator index = tiles.begin(); 
        index != tiles.end(); ++index) {
        board[index->first][index->second].setToRemove(true);
        
  };
  JewelsModel::repaint();
  //FOR each row tile position
  for (int row = 0; row < JewelsModel::boardSize; row++) {
    //FOR each column tile position
    for (int col = 0; col < JewelsModel::boardSize; col++) {
      //IF the current position of the tile is in tiles
      if (tiles.count(pair<int,int>(row, col)) != 0) {
        //SET cNewTile to current tile row
        int rNewTile = row;
         
        //WHILE the position to add the tile at is not the top most row
        while (rNewTile > 0 ) {
          //SET the current position of the tile to the one above it
          board[rNewTile][col] = board[rNewTile - 1][col];
          board[rNewTile][col].setToRemove(false);
          rNewTile--; 
        };
        //SET a new random tile at the top most position
        setRandPiece(rNewTile, col); //board[rNewTile][col] = getRandPiece();
      };
    };
  };
 
  score+= tiles.size();
};

int JewelsModel::getScore() { return score;};
set<pair<int,int>> JewelsModel::getTopBottomAdjacentTiles(int x, int y) {
  //SET tiles to new set of int pairs
  set<pair<int, int>> tiles = set<pair<int,int>>();

  //SET tile piece to the piece at x y on the board
  int tilePiece = JewelsModel::board[x][y].getPiece();
  
  //FOR each tile above the x y and is the same as tilePiece THEN
  for (int row = x; row >= 0 && board[row][y].getPiece() == tilePiece; row--) {
    //add the tile location to adjacent tiles
    tiles.insert(pair<int,int>(row, y));
  }
  //FOR each tile below the x y and is the same as tilePiece THEN
  for (int row = x; row < JewelsModel::boardSize && board[row][y].getPiece() == tilePiece; row++) {
    //add the tile location to adjacent tiles
    tiles.insert(pair<int,int>(row, y));
  }
  //RETURN the matching tiles above and below the current tile that is the same
  return tiles;
};

set<pair<int,int>> JewelsModel::getLeftRightAdjacentTiles(int x, int y) {
  //SET tiles to new set of int pairs
  set<pair<int, int>> tiles = set<pair<int,int>>();

  //SET tile piece to the piece at x y on the board
  int tilePiece = JewelsModel::board[x][y].getPiece();
  
  //FOR each tile to the left of location x y and is the same as tilePiece THEN
  for (int col = y; col >= 0 && board[x][col].getPiece() == tilePiece; col--) {
    //add the tile location to adjacent tiles
    tiles.insert(pair<int,int>(x, col));
  }
  //FOR each tile to the right of location x y and is the same as tilePiece THEN
  for (int col = y; col < JewelsModel::boardSize && board[x][col].getPiece() == tilePiece; col++) {
    //add the tile location to adjacent tiles
    tiles.insert(pair<int,int>(x, col));
  }
  //RETURN the matching tiles above and below the current tile that is the same
  return tiles;
};

set<pair<int,int>> JewelsModel::getAdjacentTiles(int x, int y) {
  //SET valid tiles to set of empty int pair
  set<pair<int,int>> validTiles = set<pair<int,int>>();

  set<pair<int,int>> validAdjacentTiles = getValidAdjacentTiles(x,y);

  for (set <pair<int,int> >::iterator tile = validAdjacentTiles.begin();
        tile != validAdjacentTiles.end(); ++tile) {
    if (getLeftRightAdjacentTiles(tile->first, tile->second).size() > similarAdjTileLimit ||
      getTopBottomAdjacentTiles(tile->first, tile->second).size() > similarAdjTileLimit)
      validTiles.insert(*tile);
  };
  return validTiles;
};

set<pair<int,int>> JewelsModel::getValidAdjacentTiles(int x, int y) {
  //SET valid tiles to set of empty int pair
  set<pair<int,int>> adjTiles = set<pair<int,int>>();
  //SET fringe to be a empty stack
  stack<pair<int,int>> fringe = stack<pair<int,int>>();
  
  //SET piece to tile piece we want to explore 
  int piece = board[x][y].getPiece();
  //add  the position of tile whose adjacent tiles we want to explore
  fringe.push(pair<int,int>(x,y));

  //WHILE the fringe contains tiles to be explored
  while (!fringe.empty()) {
    //SET point to the top most tile in the fringe
    pair<int,int> point = fringe.top();
    fringe.pop();

    //IF the tile at the point is same at the piece we want to explore and
    //the point hasn't been visited already THEN
    if (board[point.first][point.second].getPiece() == piece && 
        adjTiles.count(point) == 0) {
       //mark the point as visited
       adjTiles.insert(point);
       
       //FOR each adjacent piece
       for (vector<Dir>::const_iterator dir = JewelsModel::DIRECTIONS.begin();
            dir != JewelsModel::DIRECTIONS.end(); ++dir) {
        int newX = point.first + dir->x;
        int newY = point.second + dir->y;
        
        //IF the adjacent piece hasn't been visited
        if (isValidPoint(newX, newY))
          //add the adjacnet piece to fringe
          fringe.push(pair<int,int>(newX, newY));
       }
    }
  }

  //SET valid tiles to set of empty int pair
  set<pair<int,int>> validTiles = set<pair<int,int>>();
  
   
  for (set<pair<int,int> >::const_iterator tile = adjTiles.begin(); 
        tile != adjTiles.end(); ++tile) {
    if (validTiles.count(*tile) == 0) 
      if (getLeftRightAdjacentTiles(tile->first, tile->second).size() > similarAdjTileLimit ||
        getTopBottomAdjacentTiles(tile->first, tile->second).size() > similarAdjTileLimit)
        validTiles.insert(*tile);
  };

  //RETURN all the valid adjacent tile
  return validTiles;
};

bool JewelsModel::isValidPoint(int x, int y) {
  //IF the x and y position is inside the boarder of the board
  if ( x >= 0 && x < boardSize &&
       y >= 0 && y < boardSize) 
       //RETURN true
       return true;
  //RETURN false
  return false;
};

bool JewelsModel::isGameWon() {
  return false;
};
JewelsPiece ** JewelsModel::getBoard() {
  return createBoard();
}

JewelsPiece ** JewelsModel::createBoard() {
  //SET copyBoard to new ptr of boardSize
  JewelsPiece ** copyBoard = new JewelsPiece *[boardSize];

  //FOR each row in copyBoard
  for (int row = 0; row < boardSize; row++) {
    //SET board at the current row to array of int
    //of boardSize
    copyBoard[row] = new JewelsPiece[boardSize];
    for (int col = 0; col < boardSize; col++) {
      //SET the tile at current position in copyboard to
      //to our board model
      copyBoard[row][col].setPiece(board[row][col].getPiece());
      copyBoard[row][col].setIsSelected(board[row][col].getIsSelected());
      copyBoard[row][col].setIsVisible(board[row][col].getIsVisible());
      copyBoard[row][col].setToRemove(board[row][col].getToRemove());
    }
  };
  //RETURN the copy board
  return copyBoard;
};

int JewelsModel::getBoardSize() { return boardSize; };

void JewelsModel::setView(void (* repaint)()){
  viewSet = true;
  JewelsModel::repaint = repaint;

};
void JewelsModel::selectPiece(int x, int y) {
  board[x][y].setIsSelected(true);
  if (viewSet) {
   JewelsModel::repaint();
  };  
};

void JewelsModel::deselectPiece(int x, int y) {
  board[x][y].setIsSelected(false);
  if (viewSet) {
   JewelsModel::repaint();
  };  
};
static const Dir stuff[] = {Dir::NORTH, Dir::SOUTH, Dir::EAST, Dir::WEST};
const vector<Dir> JewelsModel::DIRECTIONS = vector<Dir>(stuff, stuff + (sizeof(Dir) * 4));