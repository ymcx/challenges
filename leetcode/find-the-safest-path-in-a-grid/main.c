#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

bool pathExists(bool *checked, const int *distance, const int gridSize,
                const int d) {
  // Reset the grid of checked positions
  for (int i = 0; i < gridSize * gridSize; ++i) {
    checked[i] = false;
  }

  const int yGoal = gridSize - 1;
  const int xGoal = gridSize - 1;
  const int iGoal = yGoal * gridSize + xGoal;

  // Initializing the queue with y=0, x=-1. This will make it so that only y=0,
  // x=0 is added after the first iteration and y=0, x=0 is handled like a
  // normal position.
  int queue[16384] = {-1};
  int items = 1;

  while (items > 0) {
    const int i = queue[--items];
    const int y = i / gridSize;
    const int x = i % gridSize;

    // For loop for the four adjacent positions
    for (int dy = -1; dy <= 1; ++dy) {
      for (int dx = abs(dy) - 1; dx <= 1 - abs(dy); ++dx) {
        if (dy == 0 && dx == 0) {
          continue;
        }

        const int ny = y + dy;
        const int nx = x + dx;

        // Out-of-bounds
        if (ny < 0 || nx < 0 || ny >= gridSize || nx >= gridSize) {
          continue;
        }

        const int ni = ny * gridSize + nx;

        // The position has been checked already
        if (checked[ni]) {
          continue;
        }
        checked[ni] = true;

        // The position is too close to a thief
        if (distance[ni] < d) {
          continue;
        }

        // We're at the end position, a path exists
        if (ni == iGoal) {
          return true;
        }

        queue[items++] = ni;
      }
    }
  }

  return false;
}

void fillDistance(int *distance, int **grid, const int gridSize) {
  for (int i = 0; i < gridSize * gridSize; ++i) {
    distance[i] = INT_MAX;
  }

  for (int y = 0; y < gridSize; ++y) {
    for (int x = 0; x < gridSize; ++x) {
      // Not a thief
      if (grid[y][x] != 1) {
        continue;
      }

      for (int d = 0; d < gridSize - 1; ++d) {
        for (int dy = -d; dy <= d; ++dy) {
          const int ny = y + dy;

          // the y coordinate is out-of-bounds
          if (ny < 0 || ny >= gridSize) {
            continue;
          }

          const int dx1 = abs(dy) - d;
          const int nx1 = x + dx1;
          const int i1 = ny * gridSize + nx1;

          // No need to check for nx1 < gridSize, since nx1 is always smaller
          // than x, which itself always resides within the grid
          if (nx1 >= 0 && distance[i1] > d) {
            distance[i1] = d;
          }

          const int dx2 = d - abs(dy);
          const int nx2 = x + dx2;
          const int i2 = ny * gridSize + nx2;

          // No need to check for nx2 >= 0, since nx2 is always larger than x,
          // which itself always resides within the grid
          if (nx2 < gridSize && distance[i2] > d) {
            distance[i2] = d;
          }
        }
      }
    }
  }
}

int largestDistance(bool *checked, const int *distance, const int gridSize) {
  int max = gridSize;
  int min = 0;

  while (min + 1 < max) {
    const int d = min + (max - min) / 2;

    if (pathExists(checked, distance, gridSize, d)) {
      min = d;
    } else {
      max = d;
    }
  }

  return min;
}

int maximumSafenessFactor(int **grid, const int gridSize,
                          const int *gridColSize) {
  int *distance = malloc(gridSize * gridSize * sizeof(int));
  bool *checked = malloc(gridSize * gridSize * sizeof(bool));

  fillDistance(distance, grid, gridSize);
  const int d = largestDistance(checked, distance, gridSize);

  free(distance);
  free(checked);

  return d;
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

void example6(void) {
  int gridRow1[3] = {1, 1, 1};
  int gridRow2[3] = {0, 1, 1};
  int gridRow3[3] = {0, 0, 0};
  int *grid[3] = {gridRow1, gridRow2, gridRow3};

  const int gridSize = 3;
  const int gridColSize[3] = {3, 3, 3};

  assert(maximumSafenessFactor(grid, gridSize, gridColSize) == 0);
}

int main(void) {
  example1();
  example2();
  example3();
  example4();
  example5();
  example6();
}
