#include <stdio.h>
#include <stdlib.h>

void sort(int *array, int p, int r) {
  if (p == r) {
    return;
  }

  sort(array, p, r - 1);

  int key = array[r];
  int i = r - 1;
  while (i >= p && key < array[i]) {
    array[i + 1] = array[i];
    --i;
  }
  array[i + 1] = key;
}

int main(void) {
  int *array = malloc(sizeof(int) * 10);
  array[0] = 4;
  array[1] = 3;
  array[2] = 2;
  array[3] = 1;
  array[4] = 5;
  array[5] = 6;
  array[6] = 0;
  array[7] = 9;
  array[8] = 8;
  array[9] = 7;

  printf("insertion rec\n");
  for (int i = 0; i < 10; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");

  sort(array, 0, 9);

  for (int i = 0; i < 10; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");

  free(array);
}
