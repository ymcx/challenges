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
  for (int y = 0; y < gridSize; ++y) {
    for (int x = 0; x < gridSize; ++x) {
      checkedGrid[y][x] = false;
    }
  }

  Pair vector[32768] = {{0, 0}};
  int items = 1;

  while (items > 0) {
    const Pair point = vector[--items];
    const int y = point.y;
    const int x = point.x;

    // The position is too close to a thief or has been checked already
    if (checkedGrid[y][x] || distanceGrid[y][x] < distance) {
      continue;
    }
    checkedGrid[y][x] = true;

    // We're at the end position, a path exists
    if (y == gridSize - 1 && x == gridSize - 1) {
      return true;
    }

    // Add the adjacent positions to the queue
    if (y + 1 < gridSize) {
      const Pair point = {y + 1, x};
      vector[items++] = point;
    }

    if (x + 1 < gridSize) {
      const Pair point = {y, x + 1};
      vector[items++] = point;
    }

    if (y - 1 >= 0) {
      const Pair point = {y - 1, x};
      vector[items++] = point;
    }

    if (x - 1 >= 0) {
      const Pair point = {y, x - 1};
      vector[items++] = point;
    }
  }

  return false;
}

void fillDistanceGrid(int **distanceGrid, int **grid, const int gridSize) {
  for (int y = 0; y < gridSize; ++y) {
    for (int x = 0; x < gridSize; ++x) {
      // Not a thief
      if (grid[y][x] != 1) {
        continue;
      }

      for (int distance = 0; distance < gridSize - 1; ++distance) {
        for (int dy = -distance; dy <= distance; ++dy) {
          const int dx = abs(dy) - distance;
          const int ny = y + dy;
          const int nx1 = x + dx;
          const int nx2 = x - dx;

          if (ny < 0 || ny >= gridSize) {
            continue;
          }

          if (nx1 >= 0 && distanceGrid[ny][nx1] > distance) {
            distanceGrid[ny][nx1] = distance;
          }

          if (nx2 < gridSize && distanceGrid[ny][nx2] > distance) {
            distanceGrid[ny][nx2] = distance;
          }
        }
      }
    }
  }
}

int smallestDistance(bool **checkedGrid, int **distanceGrid,
                     const int gridSize) {
  int max = gridSize;
  int min = 0;

  while (min + 1 < max) {
    const int distance = min + (max - min) / 2;

    if (pathExists(checkedGrid, distanceGrid, gridSize, distance)) {
      min = distance;
    } else {
      max = distance;
    }
  }

  return min;
}

int maximumSafenessFactor(int **grid, const int gridSize,
                          const int *gridColSize) {
  int **distanceGrid = malloc(gridSize * sizeof(int *));
  bool **checkedGrid = malloc(gridSize * sizeof(bool *));
  for (int y = 0; y < gridSize; ++y) {
    distanceGrid[y] = malloc(gridSize * sizeof(int));
    checkedGrid[y] = malloc(gridSize * sizeof(bool));
    for (int x = 0; x < gridSize; ++x) {
      distanceGrid[y][x] = INT_MAX;
    }
  }

  fillDistanceGrid(distanceGrid, grid, gridSize);
  const int distance = smallestDistance(checkedGrid, distanceGrid, gridSize);

  for (int y = 0; y < gridSize; ++y) {
    free(distanceGrid[y]);
    free(checkedGrid[y]);
  }
  free(distanceGrid);
  free(checkedGrid);

  return distance;
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
