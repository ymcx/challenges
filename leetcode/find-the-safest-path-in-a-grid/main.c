#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int y;
  int x;
} Pair;

bool pathExists(bool **checkedGrid, int **distanceGrid, const int gridSize,
                const int distance) {
  // Reset the grid of checked positions
  for (int y = 0; y != gridSize; ++y) {
    for (int x = 0; x != gridSize; ++x) {
      checkedGrid[y][x] = false;
    }
  }

  Pair vector[65536] = {{0, 0}};
  int items = 1;

  while (items != 0) {
    const Pair point = vector[--items];
    const int y = point.y;
    const int x = point.x;

    // Out-of-bounds
    if (y == -1 || x == -1 || y == gridSize || x == gridSize) {
      continue;
    }

    // The position is too close to a thief
    if (distanceGrid[y][x] < distance) {
      continue;
    }

    // The position has been checked already
    if (checkedGrid[y][x]) {
      continue;
    }
    checkedGrid[y][x] = true;

    // We're at the end position, a path exists
    if (y == gridSize - 1 && x == gridSize - 1) {
      return true;
    }

    // Add the adjacent positions to the queue
    const Pair point1 = {y + 1, x};
    const Pair point2 = {y, x + 1};
    const Pair point3 = {y - 1, x};
    const Pair point4 = {y, x - 1};
    vector[items++] = point1;
    vector[items++] = point2;
    vector[items++] = point3;
    vector[items++] = point4;
  }

  return false;
}

int getDistance(const int y, const int x, int **grid, const int gridSize) {
  int distance = 0;

  while (1) {
    for (int dy = -distance; dy <= distance; ++dy) {
      const int dx = abs(dy) - distance;
      const int ny = y + dy;
      const int nx1 = x + dx;
      const int nx2 = x - dx;

      if (ny < 0 || ny >= gridSize) {
        continue;
      }

      if (nx1 >= 0 && nx1 < gridSize && grid[ny][nx1] == 1) {
        return distance;
      }

      if (nx2 >= 0 && nx2 < gridSize && grid[ny][nx2] == 1) {
        return distance;
      }
    }

    ++distance;
  }

  return -1;
}

int maximumSafenessFactor(int **grid, const int gridSize,
                          const int *gridColSize) {
  int **distanceGrid = malloc(gridSize * sizeof(int *));
  bool **checkedGrid = malloc(gridSize * sizeof(bool *));
  for (int y = 0; y < gridSize; ++y) {
    distanceGrid[y] = malloc(gridSize * sizeof(int));
    checkedGrid[y] = malloc(gridSize * sizeof(bool));
    for (int x = 0; x < gridSize; ++x) {
      distanceGrid[y][x] = getDistance(y, x, grid, gridSize);
    }
  }

  int distanceMax = gridSize;
  int distanceMin = 0;
  while (distanceMin + 1 != distanceMax) {
    const int distance = distanceMin + (distanceMax - distanceMin) / 2;
    if (pathExists(checkedGrid, distanceGrid, gridSize, distance)) {
      distanceMin = distance;
    } else {
      distanceMax = distance;
    }
  }

  for (int y = 0; y != gridSize; ++y) {
    free(distanceGrid[y]);
    free(checkedGrid[y]);
  }
  free(distanceGrid);
  free(checkedGrid);

  return distanceMin;
}

void example1(void) {
  int gridRow1[3] = {1, 0, 0};
  int gridRow2[3] = {0, 0, 0};
  int gridRow3[3] = {0, 0, 1};
  int *grid[3] = {gridRow1, gridRow2, gridRow3};

  const int gridSize = 3;
  const int gridColSize[3] = {3, 3, 3};

  assert(maximumSafenessFactor(grid, gridSize, gridColSize) == 0);
}

void example2(void) {
  int gridRow1[3] = {0, 0, 1};
  int gridRow2[3] = {0, 0, 0};
  int gridRow3[3] = {0, 0, 0};
  int *grid[3] = {gridRow1, gridRow2, gridRow3};

  const int gridSize = 3;
  const int gridColSize[3] = {3, 3, 3};

  assert(maximumSafenessFactor(grid, gridSize, gridColSize) == 2);
}

void example3(void) {
  int gridRow1[4] = {0, 0, 0, 1};
  int gridRow2[4] = {0, 0, 0, 0};
  int gridRow3[4] = {0, 0, 0, 0};
  int gridRow4[4] = {1, 0, 0, 0};
  int *grid[4] = {gridRow1, gridRow2, gridRow3, gridRow4};

  const int gridSize = 4;
  const int gridColSize[4] = {4, 4, 4, 4};

  assert(maximumSafenessFactor(grid, gridSize, gridColSize) == 2);
}

void example4(void) {
  int gridRow1[3] = {0, 1, 1};
  int gridRow2[3] = {0, 1, 1};
  int gridRow3[3] = {0, 0, 1};
  int *grid[3] = {gridRow1, gridRow2, gridRow3};

  const int gridSize = 3;
  const int gridColSize[3] = {3, 3, 3};

  assert(maximumSafenessFactor(grid, gridSize, gridColSize) == 0);
}

void example5(void) {
  int gridRow01[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow02[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow03[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow04[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow05[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow06[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow07[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow08[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow09[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow10[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow11[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
  int gridRow12[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
  int gridRow13[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
  int gridRow14[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow15[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int gridRow16[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  int gridRow17[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
  int *grid[17] = {gridRow01, gridRow02, gridRow03, gridRow04, gridRow05,
                   gridRow06, gridRow07, gridRow08, gridRow09, gridRow10,
                   gridRow11, gridRow12, gridRow13, gridRow14, gridRow15,
                   gridRow16, gridRow17};

  const int gridSize = 17;
  const int gridColSize[17] = {17, 17, 17, 17, 17, 17, 17, 17, 17,
                               17, 17, 17, 17, 17, 17, 17, 17};

  assert(maximumSafenessFactor(grid, gridSize, gridColSize) == 1);
}

int main(void) {
  example1();
  example2();
  example3();
  example4();
  example5();
}
