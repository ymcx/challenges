#include <stdio.h>
#include <stdlib.h>

#define N 4

void mataddrec(int **A, int Ay, int Ax, int **B, int By, int Bx, int **C,
               int Cy, int Cx, int n) {
  if (n == 1) {
    C[Cy][Cx] += A[Ay][Ax] + B[By][Bx];
    return;
  }

  n /= 2;

  mataddrec(A, Ay + 0, Ax + 0, B, By + 0, Bx + 0, C, Cy + 0, Cx + 0, n);
  mataddrec(A, Ay + n, Ax + 0, B, By + n, Bx + 0, C, Cy + n, Cx + 0, n);
  mataddrec(A, Ay + 0, Ax + n, B, By + 0, Bx + n, C, Cy + 0, Cx + n, n);
  mataddrec(A, Ay + n, Ax + n, B, By + n, Bx + n, C, Cy + n, Cx + n, n);
}

void matadd(int **A, int **B, int **C) {
  mataddrec(A, 0, 0, B, 0, 0, C, 0, 0, N);
}

int **init(int V[N * N]) {
  int **A = malloc(sizeof(int *) * N);
  for (int i = 0; i < N; ++i) {
    A[i] = malloc(sizeof(int) * N);
    for (int j = 0; j < N; ++j) {
      A[i][j] = V[i * N + j];
    }
  }
  return A;
}

void del(int **A) {
  for (int i = 0; i < N; ++i) {
    free(A[i]);
  }
  free(A);
}

void print(int **A) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
}

int main(void) {
  int V1[N * N] = {0,   1,  2,  3, 4, 5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
  int V2[N * N] = {12, 13, 14, 15, 8, 9, 10, 11, 4, 5,  6,  7,  0,  1,  2,  4};
  int V0[N * N] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int **A = init(V1);
  int **B = init(V2);
  int **C = init(V0);

  matadd(A, B, C);

  print(C);

  del(A);
  del(B);
  del(C);
}
