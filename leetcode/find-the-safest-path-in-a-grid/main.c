#include "vector/vector.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int y;
  int x;
} Pair;

bool pathExists(int **grid, bool **thiefAura, const int gridSize,
                const int distance) {
  for (int y = 0; y < gridSize; ++y) {
    for (int x = 0; x < gridSize; ++x) {
      thiefAura[y][x] = false;
    }
  }

  // Fill the map with positions that are within the given distance from the
  // thief
  for (int y = 0; y < gridSize; ++y) {
    for (int x = 0; x < gridSize; ++x) {
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
          if (ny < 0 || nx < 0 || ny >= gridSize || nx >= gridSize) {
            continue;
          }

          // The thief is close enough to the start/end position
          if ((ny == 0 && nx == 0) ||
              (ny == gridSize - 1 && nx == gridSize - 1)) {
            return false;
          }

          thiefAura[ny][nx] = true;
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
    if (y < 0 || x < 0 || y >= gridSize || x >= gridSize) {
      continue;
    }

    // The position has been checked already
    if (thiefAura[y][x]) {
      continue;
    }
    thiefAura[y][x] = true;

    // We're at the end position, a path exists
    if (y == gridSize - 1 && x == gridSize - 1) {
      return true;
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

  return false;
}

int maximumSafenessFactor(int **grid, const int gridSize,
                          const int *gridColSize) {
  int distanceMax = gridSize;
  int distanceMin = 0;

  bool **thiefAura = malloc(gridSize * sizeof(bool *));
  for (int y = 0; y < gridSize; ++y) {
    thiefAura[y] = malloc(gridSize * sizeof(bool));
  }

  while (distanceMin + 1 < distanceMax) {
    const int distance = distanceMin + (distanceMax - distanceMin) / 2;
    if (pathExists(grid, thiefAura, gridSize, distance - 1)) {
      distanceMin = distance;
    } else {
      distanceMax = distance;
    }
  }

  for (int y = 0; y < gridSize; ++y) {
    free(thiefAura[y]);
  }
  free(thiefAura);

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

int main(void) {
  example1();
  example2();
  example3();
}
