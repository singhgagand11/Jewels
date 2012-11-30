#include "Dir.h"


Dir::Dir(int x, int y) {
  this->x = x;
  this->y = y;
};

const Dir Dir::NORTH = Dir(0, 1);
const Dir Dir::SOUTH = Dir(0, -1);
const Dir Dir::EAST = Dir(-1, 0);
const Dir Dir::WEST = Dir(1, 0);
const Dir Dir::NORTHEAST = Dir(1, -1);
const Dir Dir::NORTHWEST = Dir(1, 1);
const Dir Dir::SOUTHEAST = Dir(-1, -1);
const Dir Dir::SOUTHWEST = Dir(-1, 1);

/**
static const Dir stuff[] = {Dir::NORTH, Dir::SOUTH, Dir::EAST, Dir::WEST, 
              Dir::NORTHEAST, Dir::NORTHWEST, Dir::SOUTHEAST, Dir::SOUTHWEST};
vector<Dir> Dir::DIRECTIONS = vector<Dir>(stuff, stuff + (sizeof(Dir) * 8));
**/