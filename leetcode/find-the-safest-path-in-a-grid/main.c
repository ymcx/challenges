#include "vector/vector.h"
#include <assert.h>
#include <stdlib.h>

typedef struct {
  int y;
  int x;
} Pair;

int pathExists(int **grid, const int gridSize, const int *gridColSize,
               const int distance) {
  int **copy = malloc(gridSize * sizeof(int *));
  for (int i = 0; i < gridSize; i++) {
    copy[i] = malloc(gridColSize[i] * sizeof(int));
    for (int j = 0; j < gridColSize[i]; j++) {
      copy[i][j] = 0;
    }
  }

  // Fill the map with positions that are within the given distance from the
  // thief
  for (int y = 0; y < gridSize; ++y) {
    for (int x = 0; x < gridColSize[y]; ++x) {
      // The position contains no thief
      if (grid[y][x] == 0) {
        continue;
      }

      // Calculate the manhattan distance from the thief
      for (int dy = -distance; dy <= distance; ++dy) {
        for (int dx = -distance + abs(dy); dx <= distance - abs(dy); ++dx) {
          const int ny = y + dy;
          const int nx = x + dx;

          // Out-of-bounds
          if (ny < 0 || nx < 0 || ny >= gridSize || nx >= gridColSize[ny]) {
            continue;
          }

          // The thief is close enough to the start/end position
          if ((ny == 0 && nx == 0) ||
              (ny == gridSize - 1 && nx == gridColSize[ny] - 1)) {
            return 0;
          }

          copy[ny][nx] = 1;
        }
      }
    }
  }

  Pair start = {0, 0};
  Vector *vector = vector_create(512, sizeof(Pair));
  vector_push_back(vector, &start);

  // Decide whether a path exists from the start position to the end position
  while (!vector_empty(vector)) {
    const Pair *point = vector_back(vector);
    vector_pop_back(vector);

    const int y = point->y;
    const int x = point->x;

    // Out-of-bounds
    if (y < 0 || x < 0 || y >= gridSize || x >= gridColSize[y]) {
      continue;
    }

    // The position has been checked already
    if (copy[y][x] == 1) {
      continue;
    }
    copy[y][x] = 1;

    // We're at the end position, a path exists
    if (y == gridSize - 1 && x == gridColSize[y] - 1) {
      return 1;
    }

    // Add the adjacent positions to the queue
    const Pair point1 = {y + 1, x};
    const Pair point2 = {y, x + 1};
    const Pair point3 = {y - 1, x};
    const Pair point4 = {y, x - 1};
    vector_push_back(vector, &point1);
    vector_push_back(vector, &point2);
    vector_push_back(vector, &point3);
    vector_push_back(vector, &point4);
  }

  for (int i = 0; i < gridSize; i++) {
    free(copy[i]);
  }
  free(copy);

  return 0;
}

int maximumSafenessFactor(int **grid, const int gridSize,
                          const int *gridColSize) {
  for (int distance = gridSize - 1; 0 < distance; --distance) {
    if (pathExists(grid, gridSize, gridColSize, distance - 1)) {
      return distance;
    }
  }

  return 0;
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

int main(void) {
  example1();
  example2();
  example3();
}
