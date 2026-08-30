#include <stdio.h>
#include <stdlib.h>

#define X 4
#define Y 3

void matmul(int x, int y, int **A, int **B, int **C) {
  for (int i = 0; i < y; ++i) {
    for (int j = 0; j < y; ++j) {
      for (int k = 0; k < x; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

int **init(int x, int y, int V[x * y]) {
  int **A = malloc(sizeof(int *) * y);
  for (int i = 0; i < y; ++i) {
    A[i] = malloc(sizeof(int) * x);
    for (int j = 0; j < x; ++j) {
      A[i][j] = V[i * x + j];
    }
  }
  return A;
}

void del(int x, int y, int **A) {
  for (int i = 0; i < y; ++i) {
    free(A[i]);
  }
  free(A);
}

void print(int x, int y, int **A) {
  for (int i = 0; i < y; ++i) {
    for (int j = 0; j < x; ++j) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
}

int main(void) {
  int V1[X * Y] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  int V2[Y * X] = {2, 3, 3, 3, 5, 5, 6, 6, 9, 9, 9, 9};
  int V0[Y * Y] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int **A = init(X, Y, V1);
  int **B = init(Y, X, V2);
  int **C = init(Y, Y, V0);

  matmul(X, Y, A, B, C);

  print(Y, Y, C);

  del(X, Y, A);
  del(Y, X, B);
  del(Y, Y, C);
}
