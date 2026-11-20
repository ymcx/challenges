#include <assert.h>
#include <stddef.h>

int isZeros(const int *nums, const int numsSize) {
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] != 0) {
      return 0;
    }
  }

  return 1;
}

int isDivisible(const int *nums, const int numsSize) {
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] % 2 != 0) {
      return 0;
    }
  }

  return 1;
}

void divide(int *nums, const int numsSize) {
  for (int i = 0; i < numsSize; ++i) {
    nums[i] /= 2;
  }
}

void substract(int *nums, const int numsSize) {
  int i = 0;
  while (nums[i] % 2 == 0) {
    ++i; // i will never reach numsSize
  }

  nums[i] -= 1;
}

int minOperations(int *nums, int numsSize) {
  int i = 0;
  while (1) {
    ++i;

    if (isDivisible(nums, numsSize)) {
      divide(nums, numsSize);
      continue;
    }

    substract(nums, numsSize);

    if (isZeros(nums, numsSize)) {
      return i;
    }
  }
}

void example1(void) {
  int nums[] = {1, 5};
  int numsSize = 2;
  assert(minOperations(nums, numsSize) == 5);
}

void example2(void) {
  int nums[] = {2, 2};
  int numsSize = 2;
  assert(minOperations(nums, numsSize) == 3);
}

void example3(void) {
  int nums[] = {4, 2, 5};
  int numsSize = 3;
  assert(minOperations(nums, numsSize) == 6);
}

int main(void) {
  example1();
  example2();
  example3();
}
