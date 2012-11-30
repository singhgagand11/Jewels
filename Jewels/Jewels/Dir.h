#ifndef _DIR_
#define _DIR_
#include <vector>
using namespace std;

class Dir {
  public:
    static const Dir NORTH;
    static const Dir SOUTH;
    static const Dir EAST;
    static const Dir WEST;
    static const Dir NORTHEAST;
    static const Dir NORTHWEST;
    static const Dir SOUTHEAST;
    static const Dir SOUTHWEST;

    static vector<Dir> DIRECTIONS;
    int x;
    int y;
    Dir(int x, int y);
};
#endif
