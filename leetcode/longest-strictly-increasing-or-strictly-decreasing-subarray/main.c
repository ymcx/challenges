#include <assert.h>
#include <limits.h>
#include <stdint.h>

int longestMonotonicSubarrayDirection(int *nums, int numsSize, int direction) {
  if (numsSize <= 1) {
    return numsSize;
  }

  int result = 0;
  int tmp = 1;

  for (int i = 1; i < numsSize; ++i) {
    if (direction ? nums[i - 1] < nums[i] : nums[i - 1] > nums[i]) {
      tmp += 1;
    } else {
      tmp = 1;
    }

    if (tmp > result) {
      result = tmp;
    }
  }

  return result;
}

int longestMonotonicSubarray(int *nums, int numsSize) {
  int a = longestMonotonicSubarrayDirection(nums, numsSize, 0);
  int b = longestMonotonicSubarrayDirection(nums, numsSize, 1);
  return a > b ? a : b;
}

void example1() {
  int nums[] = {1, 4, 3, 3, 2};
  assert(longestMonotonicSubarray(nums, 5) == 2);
}

void example2() {
  int nums[] = {3, 3, 3, 3};
  assert(longestMonotonicSubarray(nums, 4) == 1);
}

void example3() {
  int nums[] = {3, 2, 1};
  assert(longestMonotonicSubarray(nums, 3) == 3);
}

int main(void) {
  example1();
  example2();
  example3();
}
