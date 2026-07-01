#include "queue.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int pathExists(int **grid, int gridSize, int *gridColSize, int distance) {
  int **copy = malloc(gridSize * sizeof(int *));
  for (int i = 0; i < gridSize; i++) {
    copy[i] = malloc(gridColSize[i] * sizeof(int));
    for (int j = 0; j < gridColSize[i]; j++) {
      copy[i][j] = 0;
    }
  }

  for (int y = 0; y < gridSize; ++y) {
    for (int x = 0; x < gridSize; ++x) {
      if (grid[y][x] == 0) {
        continue;
      }

      for (int dy = -distance; dy <= distance; ++dy) {
        for (int dx = abs(dy) - distance; dx <= distance - abs(dy); ++dx) {
          int ny = y + dy;
          int nx = x + dx;

          if (ny < 0 || nx < 0 || ny >= gridSize || nx >= gridSize) {
            continue;
          }

          if (ny == 0 && nx == 0) {
            for (int i = 0; i < gridSize; i++) {
              free(copy[i]);
            }
            free(copy);

            return 0;
          }

          if (ny == gridSize - 1 && nx == gridSize - 1) {
            for (int i = 0; i < gridSize; i++) {
              free(copy[i]);
            }
            free(copy);

            return 0;
          }

          if (copy[ny][nx] == 1) {
            for (int i = 0; i < gridSize; i++) {
              free(copy[i]);
            }
            free(copy);

            return 0;
          }

          copy[ny][nx] = 1;
        }
      }
    }
  }

  Queue *queue = malloc(sizeof(Queue));
  initializeQueue(queue);

  Pair start = {0, 0};
  enqueue(queue, start);

  while (!isEmpty(queue)) {
    Pair point = peek(queue);
    int y = point.y;
    int x = point.x;

    dequeue(queue);

    if (y < 0 || x < 0 || y >= gridSize || x >= gridSize) {
      continue;
    }

    if (copy[y][x] == 1) {
      continue;
    }

    copy[y][x] = 1;

    if (y == gridSize - 1 && x == gridSize - 1) {
      for (int i = 0; i < gridSize; i++) {
        free(copy[i]);
      }
      free(copy);

      return 1;
    }

    Pair value1 = {y + 1, x + 0};
    Pair value2 = {y + 0, x + 1};
    Pair value3 = {y - 1, x - 0};
    Pair value4 = {y - 0, x - 1};
    enqueue(queue, value1);
    enqueue(queue, value2);
    enqueue(queue, value3);
    enqueue(queue, value4);
  }

  for (int i = 0; i < gridSize; i++) {
    free(copy[i]);
  }
  free(copy);

  return 0;
}

int maximumSafenessFactor(int **grid, int gridSize, int *gridColSize) {
  for (int i = gridSize - 1; 0 < i; --i) {
    printf("%d\n", i);
    if (pathExists(grid, gridSize, gridColSize, i - 1) == 1) {
      printf("ANS = %d\n", i);
      return i;
    }
  }

  printf("ANS = 0\n");
  return 0;
}

void example1(void) {
  int gridRow1[3] = {1, 0, 0};
  int gridRow2[3] = {0, 0, 0};
  int gridRow3[3] = {0, 0, 1};
  int *grid[3] = {gridRow1, gridRow2, gridRow3};

  int gridSize = 3;
  int gridColSize[3] = {3, 3, 3};

  assert(maximumSafenessFactor(grid, gridSize, gridColSize) == 0);
}

void example2(void) {
  int gridRow1[3] = {0, 0, 1};
  int gridRow2[3] = {0, 0, 0};
  int gridRow3[3] = {0, 0, 0};
  int *grid[3] = {gridRow1, gridRow2, gridRow3};

  int gridSize = 3;
  int gridColSize[3] = {3, 3, 3};

  assert(maximumSafenessFactor(grid, gridSize, gridColSize) == 2);
}

void example3(void) {
  int gridRow1[4] = {0, 0, 0, 1};
  int gridRow2[4] = {0, 0, 0, 0};
  int gridRow3[4] = {0, 0, 0, 0};
  int gridRow4[4] = {1, 0, 0, 0};
  int *grid[4] = {gridRow1, gridRow2, gridRow3, gridRow4};

  int gridSize = 4;
  int gridColSize[4] = {4, 4, 4, 4};

  assert(maximumSafenessFactor(grid, gridSize, gridColSize) == 2);
}

int main(void) {
  example1();
  example2();
  example3();
}
