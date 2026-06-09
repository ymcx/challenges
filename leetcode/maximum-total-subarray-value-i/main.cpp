#include <cassert>
#include <climits>
#include <vector>

using namespace std;

static long long maxTotalValue(const vector<int> &nums, const long long k) {
  int minNum = INT_MAX;
  int maxNum = INT_MIN;
  for (size_t i = 0; i < nums.size(); ++i) {
    minNum = min(minNum, nums[i]);
    maxNum = max(maxNum, nums[i]);
  }

  return (maxNum - minNum) * k;
}

void example1() {
  vector<int> input = {1, 3, 2};
  assert(maxTotalValue(input, 2) == 4);
}

void example2() {
  vector<int> input = {4, 2, 5, 1};
  assert(maxTotalValue(input, 3) == 12);
}

int main() {
  example1();
  example2();
}
