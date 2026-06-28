#include <assert.h>
#include <stdlib.h>

int comp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int maximumElementAfterDecrementingAndRearranging(int *arr,
                                                  const size_t arrSize) {
  qsort(arr, arrSize, sizeof(int), comp);

  arr[0] = 1;
  for (size_t i = 1; i < arrSize; ++i) {
    const int a = arr[i - 1];
    const int b = arr[i];

    if (a + 1 < b) {
      arr[i] = a + 1;
    }
  }

  return arr[arrSize - 1];
}

void example1(void) {
  int input[5] = {2, 2, 1, 2, 1};
  assert(maximumElementAfterDecrementingAndRearranging(input, 5) == 2);
}

void example2(void) {
  int input[3] = {100, 1, 1000};
  assert(maximumElementAfterDecrementingAndRearranging(input, 3) == 3);
}

void example3(void) {
  int input[5] = {1, 2, 3, 4, 5};
  assert(maximumElementAfterDecrementingAndRearranging(input, 5) == 5);
}

void example4(void) {
  int input[3] = {73, 98, 9};
  assert(maximumElementAfterDecrementingAndRearranging(input, 3) == 3);
}

int main(void) {
  example1();
  example2();
  example3();
  example4();
}
