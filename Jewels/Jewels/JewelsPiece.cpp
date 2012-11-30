 #include "JewelsPiece.h"

JewelsPiece::JewelsPiece(int piece): piece(piece) {};
JewelsPiece::JewelsPiece(): piece(-1), isSelected(false), isVisible(false), toRemove(false){};

void JewelsPiece::setIsSelected(bool isSelected){JewelsPiece::isSelected = isSelected;};
void JewelsPiece::setIsVisible(bool isVisible) {JewelsPiece::isVisible = isVisible;};
void JewelsPiece::setToRemove(bool toRemove) {JewelsPiece::toRemove = toRemove;}; 
void JewelsPiece::setPiece(int piece) {JewelsPiece::piece = piece;};
int JewelsPiece::getIsSelected() {return JewelsPiece::isSelected;};
bool JewelsPiece::getIsVisible() {return JewelsPiece::isVisible;};
bool JewelsPiece::getToRemove() {return JewelsPiece::toRemove;};
int JewelsPiece::getPiece() {return piece;};

  