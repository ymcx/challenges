#include <assert.h>
#include <stdlib.h>

int add(int (*queue)[3], int i, int gridSize, int *gridColSize, int y, int x,
        int d) {
  if (y >= gridSize || x >= gridColSize[y]) {
    return 0;
  }

  queue[i][0] = y;
  queue[i][1] = x;
  queue[i][2] = d;

  return 1;
}

int isresult(int **grid, int gridSize, int *gridColSize, int y, int x) {
  int result = 0;
  int (*queue)[3] = malloc(sizeof(int[3]) * 1000);
  int i = add(queue, 0, gridSize, gridColSize, 0, 0, 0);
  while (i != 0) {
    --i;
    int y = queue[i][0];
    int x = queue[i][1];
    int d = queue[i][2];

    if (y == gridSize - 1 && x == gridColSize[y] - 1) {
      ++result;
      continue;
    }

    if (grid[y][x]) {
      if (d == 1) {
        i += add(queue, i, gridSize, gridColSize, y + 1, x, 0);
      } else {
        i += add(queue, i, gridSize, gridColSize, y, x + 1, 1);
      }
      continue;
    }

    i += add(queue, i, gridSize, gridColSize, y + 1, x, 0);
    i += add(queue, i, gridSize, gridColSize, y, x + 1, 1);
  }

  return result;
}

int uniquePaths(int **grid, int gridSize, int *gridColSize) {
  // int result = 0;
  // int (*queue)[3] = malloc(sizeof(int[3]) * 1000);
  // int i = add(queue, 0, gridSize, gridColSize, 0, 0, 0);

  int **rigi = malloc(sizeof(int *) * gridSize);
  for (int j = 0; j < gridSize; ++j) {
    rigi[j] = malloc(sizeof(int) * gridColSize[j]);
    for (int k = 0; k < gridColSize[j]; ++k) {
      rigi[j][k] = 0;
    }
    int a = gridSize - 1 + gridColSize[gridSize - 1] - 2;
    while (a >= 0) {
      int y = 0;
      int x = a;
      while (x >= 0) {
        if (y < gridSize && x < gridColSize[y]) {
          rigi[y][x] = isresult(grid, gridSize, gridColSize, y, x);
        }

        y += 1;
        x -= 1;
      }

      --a;
    }
  }

  return rigi[0][0];
}

int example1() {
  int gridSize = 3;
  int gridColSize[3] = {3, 3, 3};
  int **grid = malloc(sizeof(int *) * gridSize);
  for (int i = 0; i < gridSize; ++i) {
    grid[i] = malloc(sizeof(int) * gridColSize[i]);
    for (int j = 0; j < gridColSize[i]; ++j) {
      grid[i][j] = 0;
    }
  }
  grid[0][1] = 1;
  grid[1][2] = 1;
  grid[2][0] = 1;

  int result = uniquePaths(grid, gridSize, gridColSize) == 5;
  for (int i = 0; i < gridSize; ++i) {
    free(grid[i]);
  }
  free(grid);

  return result;
}

int example2() {
  int gridSize = 2;
  int gridColSize[2] = {2, 2};
  int **grid = malloc(sizeof(int *) * gridSize);
  for (int i = 0; i < gridSize; ++i) {
    grid[i] = malloc(sizeof(int) * gridColSize[i]);
    for (int j = 0; j < gridColSize[i]; ++j) {
      grid[i][j] = 0;
    }
  }

  int result = uniquePaths(grid, gridSize, gridColSize) == 2;
  for (int i = 0; i < gridSize; ++i) {
    free(grid[i]);
  }
  free(grid);

  return result;
}

int example3() {
  int gridSize = 2;
  int gridColSize[2] = {3, 3};
  int **grid = malloc(sizeof(int *) * gridSize);
  for (int i = 0; i < gridSize; ++i) {
    grid[i] = malloc(sizeof(int) * gridColSize[i]);
    for (int j = 0; j < gridColSize[i]; ++j) {
      grid[i][j] = 0;
    }
  }
  grid[0][1] = 1;
  grid[0][2] = 1;
  grid[1][0] = 1;
  grid[1][1] = 1;

  int result = uniquePaths(grid, gridSize, gridColSize) == 1;
  for (int i = 0; i < gridSize; ++i) {
    free(grid[i]);
  }
  free(grid);

  return result;
}

int main(void) {
  assert(example1());
  assert(example2());
  assert(example3());
}
