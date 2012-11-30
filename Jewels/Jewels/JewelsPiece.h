#ifndef _JEWELS_PIECE_
#define _JEWELS_PIECE_
class JewelsPiece
{
  private:
  int piece;
  bool isSelected;
  bool isVisible;
  bool toRemove;
  

  public:
  JewelsPiece(int piece);
  JewelsPiece();
  void setIsSelected(bool selected);
  void setIsVisible(bool isVisible);
  void setToRemove(bool toRemove);
  void setPiece(int piece);
  int getIsSelected();
  bool getIsVisible();
  bool getToRemove();
  int getPiece();
    
};
#endif