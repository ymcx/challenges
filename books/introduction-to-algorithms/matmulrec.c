#include <stdio.h>
#include <stdlib.h>

#define N 4

void matmulrec(int **A, int Ay, int Ax, int **B, int By, int Bx, int **C,
               int Cy, int Cx, int n) {
  if (n == 1) {
    C[Cy][Cx] += A[Ay][Ax] * B[By][Bx];
    return;
  }

  n /=2;

  matmulrec(A, Ay+0*n, Ax+0*n, B, By+0*n, Bx+0*n, C, Cy+0*n, Cx+0*n, n);
  matmulrec(A, Ay+0*n, Ax+0*n, B, By+0*n, Bx+1*n, C, Cy+0*n, Cx+1*n, n);
  matmulrec(A, Ay+1*n, Ax+0*n, B, By+0*n, Bx+0*n, C, Cy+1*n, Cx+0*n, n);
  matmulrec(A, Ay+1*n, Ax+0*n, B, By+0*n, Bx+1*n, C, Cy+1*n, Cx+1*n, n);

  matmulrec(A, Ay+0*n, Ax+1*n, B, By+1*n, Bx+0*n, C, Cy+0*n, Cx+0*n, n);
  matmulrec(A, Ay+0*n, Ax+1*n, B, By+1*n, Bx+1*n, C, Cy+0*n, Cx+1*n, n);
  matmulrec(A, Ay+1*n, Ax+1*n, B, By+1*n, Bx+0*n, C, Cy+1*n, Cx+0*n, n);
  matmulrec(A, Ay+1*n, Ax+1*n, B, By+1*n, Bx+1*n, C, Cy+1*n, Cx+1*n, n);
}

void matmul(int **A, int **B, int **C) {
  matmulrec(A, 0, 0, B, 0, 0, C, 0, 0, N);
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
  int V1[N * N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  int V2[N * N] = {12, 13, 14, 15, 8, 9, 10, 11, 4, 5, 6, 7, 0, 1, 2, 3};
  int V0[N * N] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int **A = init(V1);
  int **B = init(V2);
  int **C = init(V0);

  matmul(A, B, C);

  print(C);

  del(A);
  del(B);
  del(C);
}
