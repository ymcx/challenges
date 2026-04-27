#include <cassert>
#include <set>
#include <vector>

using namespace std;

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  NONE,
};

struct Position {
  int y;
  int x;
  Direction dir;

  void moveDown() {
    dir = DOWN;
    ++y;
  }
  void moveUp() {
    dir = UP;
    --y;
  }
  void moveRight() {
    dir = RIGHT;
    ++x;
  }
  void moveLeft() {
    dir = LEFT;
    --x;
  }
};

void doMove(const int street, Position &pos, const bool invert) {
  switch (street) {
  case 1:
    invert != (pos.dir == LEFT) ? pos.moveLeft() : pos.moveRight();
    break;
  case 2:
    invert != (pos.dir == UP) ? pos.moveUp() : pos.moveDown();
    break;
  case 3:
    invert != (pos.dir == UP) ? pos.moveLeft() : pos.moveDown();
    break;
  case 4:
    invert != (pos.dir == UP) ? pos.moveRight() : pos.moveDown();
    break;
  case 5:
    invert != (pos.dir == DOWN) ? pos.moveLeft() : pos.moveUp();
    break;
  case 6:
    invert != (pos.dir == LEFT) ? pos.moveUp() : pos.moveRight();
    break;
  }
}

bool doConnect(const Direction old_dir, const int street) {
  switch (old_dir) {
  case UP:
    return street == 2 || street == 3 || street == 4;
  case DOWN:
    return street == 2 || street == 5 || street == 6;
  case LEFT:
    return street == 1 || street == 4 || street == 6;
  case RIGHT:
    return street == 1 || street == 3 || street == 5;
  case NONE:
    return true;
  default:
    return false;
  }
}

bool hasValidPath(vector<vector<int>> &grid, bool invert_direction) {
  const int max_y = grid.size() - 1;
  const int max_x = grid[0].size() - 1;
  Position pos = {0, 0, NONE};
  set<pair<int, int>> travelled;

  while (true) {
    const pair<int, int> point = {pos.y, pos.x};
    if (travelled.contains(point)) {
      return false;
    }
    travelled.insert(point);

    const int street = grid[pos.y][pos.x];

    // Check if the moved direction and street align
    if (!doConnect(pos.dir, street)) {
      return false;
    }

    // Goal
    if (pos.y == max_y && pos.x == max_x) {
      return true;
    }

    doMove(street, pos, invert_direction);
    invert_direction = false;

    // Out-of-bounds
    if (pos.y < 0 || pos.x < 0 || pos.y > max_y || pos.x > max_x) {
      return false;
    }
  }
}

bool hasValidPath(vector<vector<int>> &grid) {
  return hasValidPath(grid, false) || hasValidPath(grid, true);
}

int main() {
  vector<vector<int>> grid1 = {{2, 4, 3}, {6, 5, 2}};
  vector<vector<int>> grid2 = {{1, 2, 1}, {1, 2, 1}};
  vector<vector<int>> grid3 = {{1, 1, 2}};

  assert(hasValidPath(grid1));
  assert(!hasValidPath(grid2));
  assert(!hasValidPath(grid3));
}
