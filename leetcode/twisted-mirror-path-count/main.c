#include <assert.h>
#include <stdlib.h>

int solution_amount(int (**cache)[2], int **grid, const int y_max,
                    const int x_max, const int y, const int x, const int d) {
  if (y == y_max || x == x_max) {
    return 0;
  }

  if (cache[y][x][d] != -1) {
    return cache[y][x][d];
  }

  if (d == 1 && grid[y][x]) {
    return solution_amount(cache, grid, y_max, x_max, y + 1, x, 0);
  }

  if (d == 0 && grid[y][x]) {
    return solution_amount(cache, grid, y_max, x_max, y, x + 1, 1);
  }

  const int a = solution_amount(cache, grid, y_max, x_max, y + 1, x, 0);
  const int b = solution_amount(cache, grid, y_max, x_max, y, x + 1, 1);
  return (a + b) % 1000000007;
}

int uniquePaths(int **grid, const int gridSize, const int *gridColSize) {
  int y_max = gridSize;
  int x_max = gridColSize[0];

  int (**cache)[2] = malloc(sizeof(int *[2]) * y_max);
  for (int y = 0; y < y_max; ++y) {
    cache[y] = malloc(sizeof(int[2]) * x_max);
    for (int x = 0; x < x_max; ++x) {
      cache[y][x][0] = -1;
      cache[y][x][1] = -1;
    }
  }
  cache[y_max - 1][x_max - 1][0] = 1;
  cache[y_max - 1][x_max - 1][1] = 1;

  for (int i = y_max + x_max - 3; i >= 0; --i) {
    for (int y = 0, x = i; x >= 0; ++y, --x) {
      if (y >= y_max || x >= x_max) {
        continue;
      }

      cache[y][x][0] = solution_amount(cache, grid, y_max, x_max, y, x, 0);
      if (grid[y][x]) {
        cache[y][x][1] = solution_amount(cache, grid, y_max, x_max, y, x, 1);
      } else {
        cache[y][x][1] = cache[y][x][0];
      }
    }
  }

  const int result = cache[0][0][0];

  for (int y = 0; y < y_max; ++y) {
    free(cache[y]);
  }
  free(cache);

  return result;
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

int example4() {
  int gridSize = 1000;
  int gridColSize[1] = {gridSize};
  int **grid = malloc(sizeof(int *) * gridSize);
  for (int i = 0; i < gridSize; ++i) {
    grid[i] = malloc(sizeof(int) * gridColSize[0]);
    for (int j = 0; j < gridColSize[0]; ++j) {
      grid[i][j] = 0;
    }
  }

  int result = uniquePaths(grid, gridSize, gridColSize) == 965601742;
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
  assert(example4());
}
