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

  Pair vector[16384] = {{0, 0}};
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

int getDistance(const int y1, const int x1, int **grid, const int gridSize) {
  int distance = INT_MAX;

  for (int y2 = 0; y2 != gridSize; ++y2) {
    for (int x2 = 0; x2 != gridSize; ++x2) {
      // No thief at the position, skip
      if (grid[y2][x2] == 0) {
        continue;
      }

      // Calculate the distance from the given coordinates to this thief
      const int newDistance = abs(y2 - y1) + abs(x2 - x1);
      if (newDistance < distance) {
        distance = newDistance;
      }
    }
  }

  return distance;
}

int maximumSafenessFactor(int **grid, const int gridSize,
                          const int *gridColSize) {
  int distanceMax = gridSize;
  int distanceMin = 0;

  int **distanceGrid = malloc(gridSize * sizeof(int *));
  bool **checkedGrid = malloc(gridSize * sizeof(bool *));
  for (int y = 0; y != gridSize; ++y) {
    distanceGrid[y] = malloc(gridSize * sizeof(int));
    checkedGrid[y] = malloc(gridSize * sizeof(bool));
    for (int x = 0; x != gridSize; ++x) {
      distanceGrid[y][x] = getDistance(y, x, grid, gridSize);
    }
  }

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

int main(void) {
  example1();
  example2();
  example3();
  example4();
}
