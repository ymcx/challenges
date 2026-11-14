#include <assert.h>
#include <stdlib.h>
#include <string.h>

int comp(const void *a, const void *b) {
  const int x = *(const int *)a;
  const int y = *(const int *)b;
  return x < y;
}

long long findAnswer(const int *nums1, const int *nums2, const int n,
                     const int i, const int k) {
  int p = 0;
  int *potential = malloc(sizeof(*potential) * n);
  for (int j = 0; j < n; ++j) {
    if (nums1[j] < nums1[i]) {
      potential[p++] = nums2[j];
    }
  }

  long long answer = 0;
  qsort(potential, p, sizeof(*potential), comp);
  for (int i = 0; i < k && i < p; ++i) {
    answer += potential[i];
  }

  free(potential);
  return answer;
}

long long *findMaxSum(const int *nums1, const int nums1Size, const int *nums2,
                      const int nums2Size, const int k, int *returnSize) {
  const int n = nums1Size;
  long long *answer = malloc(sizeof(*answer) * n);
  *returnSize = n;

  for (int i = 0; i < n; ++i) {
    answer[i] = findAnswer(nums1, nums2, n, i, k);
  }

  return answer;
}

void example1(void) {
  const int nums1[] = {4, 2, 1, 5, 3};
  const int nums2[] = {10, 20, 30, 40, 50};
  const long long expected[] = {80, 30, 0, 80, 50};
  int returnSize = 0;
  long long *result = findMaxSum(nums1, 5, nums2, 5, 2, &returnSize);
  assert(!memcmp(expected, result, sizeof(expected)));
  free(result);
}

void example2(void) {
  const int nums1[] = {2, 2, 2, 2};
  const int nums2[] = {3, 1, 2, 3};
  const long long expected[] = {0, 0, 0, 0};
  int returnSize = 0;
  long long *result = findMaxSum(nums1, 4, nums2, 4, 1, &returnSize);
  assert(!memcmp(expected, result, sizeof(expected)));
  free(result);
}

int main(void) {
  example1();
  example2();
}
