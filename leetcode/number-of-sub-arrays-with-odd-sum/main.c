#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

int numOfSubarrays(int *arr, int arrSize) {
  bool prefix = false;
  long count = 0;
  long odd = 0;
  long even = 1;

  for (size_t i = 0; i < arrSize; ++i) {
    prefix ^= arr[i] % 2;
    count += prefix ? even : odd;
    even += !prefix;
    odd += prefix;
  }

  return (int)(count % 1000000007);
}

void example1(void) {
  int arr[] = {1, 3, 5};
  int arrSize = 3;
  assert(numOfSubarrays(arr, arrSize) == 4);
}

void example2(void) {
  int arr[] = {2, 4, 6};
  int arrSize = 3;
  assert(numOfSubarrays(arr, arrSize) == 0);
}

void example3(void) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  int arrSize = 7;
  assert(numOfSubarrays(arr, arrSize) == 16);
}

int main(void) {
  example1();
  example2();
  example3();
}
