#include <stdio.h>
#include <stdlib.h>

void sort(int *array) {
  int n = 5;

  for (int i = 0; i < n - 1; ++i) {
    for (int j = n - 1; j > i; --j) {
      if (array[j] < array[j - 1]) {
        int temp = array[j - 1];
        array[j - 1] = array[j];
        array[j] = temp;
      }
    }
  }
}

int main(void) {
  int *array = malloc(sizeof(int) * 5);
  array[0] = 4;
  array[1] = 2;
  array[2] = 3;
  array[3] = 1;
  array[4] = 0;

  printf("bubblesort\n");
  for (int i = 0; i < 5; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");

  sort(array);

  for (int i = 0; i < 5; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");

  free(array);
}
