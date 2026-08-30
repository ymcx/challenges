#include <stdio.h>
#include <stdlib.h>

int binary_search(int *array, int value, int p, int r) {
  while (1) {
    int q = (p + r) / 2;

    if (array[q] == value) {
      return q;
    } else if (array[q] > value) {
      r = q - 1;
    } else if (array[q] < value) {
      p = q + 1;
    }

    if (q == r) {
      return -1;
    }
  }
}

int main(void) {
  int *array = malloc(sizeof(int) * 2);
  array[0] = 10;
  array[1] = 20;

  printf("binary search\n");
  printf("%d\n", binary_search(array, 20, 0, 1));

  free(array);
}
