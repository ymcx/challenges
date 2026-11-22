#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

int maximumBeauty(int *nums, int numsSize, int k) {
  int numsMax = INT_MIN;
  int numsMin = INT_MAX;
  for (int i = 0; i < numsSize; ++i) {
    numsMax = numsMax < nums[i] ? nums[i] : numsMax;
    numsMin = numsMin > nums[i] ? nums[i] : numsMin;
  }
  const int numsSpan = numsMax - numsMin;

  int *frequencies = calloc(numsSpan + 1, sizeof(*frequencies));
  for (int i = 0; i < numsSize; ++i) {
    const int num = nums[i] - numsMin;
    frequencies[num] += 1;
  }

  int max = INT_MIN;
  int sum = 0;
  for (int i = -k; i <= numsSpan - k; ++i) {
    const int low = i - k - 1;
    const int high = i + k;
    sum -= low >= 0 ? frequencies[low] : 0;
    sum += high <= numsMax ? frequencies[high] : 0;
    max = max < sum ? sum : max;
  }

  free(frequencies);
  return max;
}

void example1(void) {
  int nums[] = {4, 6, 1, 2};
  int numsSize = 4;
  int k = 2;
  assert(maximumBeauty(nums, numsSize, k) == 3);
}

void example2(void) {
  int nums[] = {1, 1, 1, 1};
  int numsSize = 4;
  int k = 10;
  assert(maximumBeauty(nums, numsSize, k) == 4);
}

void example3(void) {
  int nums[] = {1, 1, 1, 1};
  int numsSize = 4;
  int k = 0;
  assert(maximumBeauty(nums, numsSize, k) == 4);
}

void example4(void) {
  int nums[] = {13, 46, 71};
  int numsSize = 3;
  int k = 29;
  assert(maximumBeauty(nums, numsSize, k) == 3);
}

int main(void) {
  example1();
  example2();
  example3();
  example4();
}
