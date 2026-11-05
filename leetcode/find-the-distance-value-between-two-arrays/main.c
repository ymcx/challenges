#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int findTheDistanceValue(int *arr1, int arr1Size, int *arr2, int arr2Size,
                         int d) {
  int result = arr1Size;
  for (int i = 0; i < arr1Size; ++i) {
    for (int j = 0; j < arr2Size; ++j) {
      if (abs(arr1[i] - arr2[j]) <= d) {
        --result;
        break;
      }
    }
  }

  return result;
}

int example1() {
  int arr1[3] = {4, 5, 8};
  int arr1Size = 3;
  int arr2[4] = {10, 9, 1, 8};
  int arr2Size = 4;
  int d = 2;
  return findTheDistanceValue(arr1, arr1Size, arr2, arr2Size, d) == 2;
}

int example2() {
  int arr1[4] = {1, 4, 2, 3};
  int arr1Size = 4;
  int arr2[6] = {-4, -3, 6, 10, 20, 30};
  int arr2Size = 6;
  int d = 3;
  return findTheDistanceValue(arr1, arr1Size, arr2, arr2Size, d) == 2;
}

int example3() {
  int arr1[4] = {2, 1, 100, 3};
  int arr1Size = 4;
  int arr2[5] = {-5, -2, 10, -3, 7};
  int arr2Size = 5;
  int d = 6;
  return findTheDistanceValue(arr1, arr1Size, arr2, arr2Size, d) == 1;
}

int main(void) {
  assert(example1());
  assert(example2());
  assert(example3());
}
