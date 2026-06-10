#include <algorithm>
#include <cassert>
#include <climits>
#include <vector>

using namespace std;

static int calculateValue(const vector<int> &nums,
                          const pair<size_t, size_t> &boundary) {
  int minValue = INT_MAX;
  int maxValue = INT_MIN;
  for (size_t i = boundary.first; i <= boundary.second; ++i) {
    minValue = min(minValue, nums[i]);
    maxValue = max(maxValue, nums[i]);
  }

  return maxValue - minValue;
}

static bool comp(const pair<size_t, size_t> &a, const pair<size_t, size_t> &b,
                 const vector<int> &nums) {
  return calculateValue(nums, a) > calculateValue(nums, b);
}

static vector<pair<size_t, size_t>> getBoundaries(const vector<int> &nums,
                                                  const size_t k) {
  vector<pair<size_t, size_t>> boundaries;
  for (size_t start = 0; start < nums.size(); ++start) {
    for (size_t end = start + 1; end < nums.size(); ++end) {
      boundaries.emplace_back(start, end);
    }
  }

  const size_t length = min(k, boundaries.size());
  const auto comp_fun = [&nums](const pair<size_t, size_t> &a,
                                const pair<size_t, size_t> &b) {
    return comp(a, b, nums);
  };
  partial_sort(boundaries.begin(), boundaries.begin() + length,
               boundaries.end(), comp_fun);

  return boundaries;
}

static long long maxTotalValue(const vector<int> &nums, const size_t k) {
  const vector<pair<size_t, size_t>> boundaries = getBoundaries(nums, k);
  const size_t length = min(k, boundaries.size());

  long long result = 0;
  for (size_t i = 0; i < length; ++i) {
    result += calculateValue(nums, boundaries[i]);
  }

  return result;
}

void example1() {
  vector<int> input = {1, 3, 2};
  assert(maxTotalValue(input, 2) == 4);
}

void example2() {
  vector<int> input = {4, 2, 5, 1};
  assert(maxTotalValue(input, 3) == 12);
}

void example3() {
  vector<int> input = {11, 8};
  assert(maxTotalValue(input, 2) == 3);
}

void example4() {
  vector<int> input = {9, 9, 37};
  assert(maxTotalValue(input, 2) == 56);
}

void example5() {
  vector<int> input = {18, 36, 6};
  assert(maxTotalValue(input, 3) == 78);
}

int main() {
  example1();
  example2();
  example3();
  example4();
  example5();
}
