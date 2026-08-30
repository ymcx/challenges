#include <limits.h>
#include <stdio.h>

void sort(int array[10]) {
  for (int j = 0; j < 10; ++j) {
    int minNum = INT_MAX;
    int minInd = -1;

    for (int i = j; i < 10; ++i) {
      if (array[i] < minNum) {
        minNum = array[i];
        minInd = i;
      }
    }

    array[minInd] = array[j];
    array[j] = minNum;
  }
}

int main(void) {
  int array[10] = {6, 3, 2, 8, 4, 0, 9, 1, 5, 7};
  for (int i = 0; i < 10; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");

  sort(array);

  for (int i = 0; i < 10; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
}
