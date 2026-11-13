#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

int max_index(const int *arr, const int n) {
  int j = 0;
  for (int i = 1; i < n; ++i) {
    if (arr[i] > arr[j]) {
      j = i;
    }
  }

  return j;
}

void flip(int *arr, const int k) {
  for (int i = 0, j = k; i < j; ++i, --j) {
    const int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }
}

// https://en.wikipedia.org/wiki/Pancake_sorting
int *pancakeSort(int *arr, const int arrSize, int *returnSize) {
  int *flips = malloc(sizeof(int) * 10 * arrSize);
  int i = 0;

  for (int n = arrSize; n > 1; --n) {
    const int max = max_index(arr, n);
    if (max != n - 1) {
      if (max != 0) {
        flip(arr, max);
        flips[i++] = max + 1;
      }
      flip(arr, n - 1);
      flips[i++] = n;
    }
  }

  flips = realloc(flips, sizeof(int) * i);
  *returnSize = i;

  return flips;
}

int is_sorted(const int *arr, const int arrSize) {
  for (int i = 1; i < arrSize; ++i) {
    if (arr[i - 1] > arr[i]) {
      return false;
    }
  }

  return true;
}

void example1() {
  const int arrSize = 4;
  int arr[] = {3, 2, 4, 1};
  int flipsSize = 0;
  int *flips = pancakeSort(arr, arrSize, &flipsSize);
  assert(flipsSize < 10 * arrSize);
  assert(is_sorted(arr, arrSize));
  free(flips);
}

void example2() {
  const int arrSize = 3;
  int arr[] = {1, 2, 3};
  int flipsSize = 0;
  int *flips = pancakeSort(arr, arrSize, &flipsSize);
  assert(flipsSize < 10 * arrSize);
  assert(is_sorted(arr, arrSize));
  free(flips);
}

int main(void) {
  example1();
  example2();
}
