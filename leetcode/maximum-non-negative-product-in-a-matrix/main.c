#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double **makeEmptyMatrix(const int width, const int height) {
  double **matrix = malloc(height * sizeof(double *));
  for (int y = 0; y < height; ++y) {
    matrix[y] = malloc(width * sizeof(double));
    for (int x = 0; x < width; ++x) {
      matrix[y][x] = 0.0;
    }
  }
  return matrix;
}

void freeMatrix(const int height, double **matrix) {
  for (int y = 0; y < height; ++y) {
    free(matrix[y]);
  }
  free(matrix);
}

double **fillGrid(const int width, const int height,
                  const double grid_temp[height][width]) {
  double **grid = makeEmptyMatrix(width, height);
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      grid[y][x] = grid_temp[y][x];
    }
  }
  return grid;
}

int getBestAction(const int y, const int x, const int fy, const int fx,
                  double **state) {
  double best_reward = 0.0;
  int best_action = -1;

  if (y < fy && state[y + 1][x] > best_reward) {
    best_reward = state[y + 1][x];
    best_action = 0;
  }
  if (y > 0 && state[y - 1][x] > best_reward) {
    best_reward = state[y - 1][x];
    best_action = 1;
  }
  if (x < fx && state[y][x + 1] > best_reward) {
    best_reward = state[y][x + 1];
    best_action = 2;
  }
  if (x > 0 && state[y][x - 1] > best_reward) {
    best_reward = state[y][x - 1];
    best_action = 3;
  }

  return best_action;
}

void maxProductPath(const int width, const int height, double **grid) {
  const int random_move_chance = 20;
  const double alpha = 0.5;
  const double gamma = 0.9;
  const int iterations = 1000;

  double **qvalues = makeEmptyMatrix(width, height);
  int y, x, ly, lx, fy = height - 1, fx = width - 1;
  double r;

  for (int i = 0; i < iterations; ++i) {
    y = 0, x = 0, ly = 0, lx = 0;
    r = 0.0;

    while (y != fy || x != fx) {
      ly = y;
      lx = x;

      if (rand() % 101 <= random_move_chance) {
        // Take a random move
        switch (rand() % 4) {
        case 0:
          if (y < fy)
            ++y;
          break;
        case 1:
          if (y > 0)
            --y;
          break;
        case 2:
          if (x < fx)
            ++x;
          break;
        case 3:
          if (x > 0)
            --x;
          break;
        }
      } else {
        // Take an optimal move
        switch (getBestAction(y, x, fy, fx, qvalues)) {
        case 0:
          ++y;
          break;
        case 1:
          --y;
          break;
        case 2:
          ++x;
          break;
        case 3:
          --x;
          break;
        }
      }

      double best_reward = 0.0;
      switch (getBestAction(ly, lx, fy, fx, qvalues)) {
      case 0:
        best_reward = qvalues[ly + 1][lx];
        break;
      case 1:
        best_reward = qvalues[ly - 1][lx];
        break;
      case 2:
        best_reward = qvalues[ly][lx + 1];
        break;
      case 3:
        best_reward = qvalues[ly][lx - 1];
        break;
      }

      r += log(fabs(grid[ly][lx]));
      int sign = grid[ly][lx] > 0 ? 1 : -1;
      qvalues[ly][lx] = (1.0 - alpha) * qvalues[ly][lx] +
                        alpha * (r * sign + gamma * best_reward);
    }
  }

  // Print the Q-Values
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      printf("%f ", qvalues[y][x]);
    }
    printf("\n");
  }

  freeMatrix(height, qvalues);
}

int main(void) {
  srand(time(NULL));

  const int width = 3;
  const int height = 3;
  const double grid_temp[3][3] = {{1, -2, 1}, {1, -2, 1}, {3, -4, 1}};
  double **grid = fillGrid(width, height, grid_temp);
  maxProductPath(width, height, grid);

  freeMatrix(height, grid);
}
