#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *list, const size_t i, const size_t j) {
  const int tmp = list[i];
  list[i] = list[j];
  list[j] = tmp;
}

void partition(int *list, size_t left, size_t right, size_t *lt, size_t *gt,
               const int value) {
  size_t i = left;
  while (i <= right) {
    if (list[i] < value) {
      swap(list, i, left);
      ++left;
      ++i;
    } else if (list[i] > value) {
      swap(list, i, right);
      --right;
    } else {
      ++i;
    }
  }

  *lt = left;
  *gt = right;
}

int findKthLargest(int *nums, int numsSize, int k) {
  size_t left = 0;
  size_t right = numsSize - 1;
  k = numsSize - k;

  while (left != right) {
    const size_t index = left + (right - left) / 2;
    const int pivot = nums[index];

    size_t partitionLeft, partitionRight;
    partition(nums, left, right, &partitionLeft, &partitionRight, pivot);

    if (k < partitionLeft) {
      right = partitionLeft - 1;
      continue;
    }

    if (k > partitionRight) {
      left = partitionRight + 1;
      continue;
    }

    return nums[k];
  }

  return nums[left];
}

void example1(void) {
  int nums[] = {3, 2, 1, 5, 6, 4};
  int numsSize = 6;
  int k = 2;
  assert(findKthLargest(nums, numsSize, k) == 5);
}

void example2(void) {
  int nums[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
  int numsSize = 9;
  int k = 4;
  assert(findKthLargest(nums, numsSize, k) == 4);
}

void example3(void) {
  int nums[] = {-1, 2, 0};
  int numsSize = 3;
  int k = 1;
  assert(findKthLargest(nums, numsSize, k) == 2);
}

void example4(void) {
  int numsSize = 40000;
  int *nums = malloc(sizeof(*nums) * numsSize);
  for (int i = 5; i < numsSize; ++i) {
    nums[i] = 1;
  }
  nums[0] = 1;
  nums[1] = 2;
  nums[2] = 3;
  nums[3] = 4;
  nums[4] = 5;
  int k = 5000;
  assert(findKthLargest(nums, numsSize, k) == 1);
  free(nums);
}

int main(void) {
  example1();
  example2();
  example3();
  example4();
}
