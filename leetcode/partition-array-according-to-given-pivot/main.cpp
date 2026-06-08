#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

vector<int> pivotArray(vector<int> &nums, int pivot) {
  vector<int> output;
  output.reserve(nums.size());

  // Smaller than pivot
  for (const int i : nums) {
    if (i < pivot) {
      output.push_back(i);
    }
  }

  // Equal to pivot
  const int n = count(nums.begin(), nums.end(), pivot);
  output.insert(output.end(), n, pivot);

  // Larger than pivot
  for (const int i : nums) {
    if (i > pivot) {
      output.push_back(i);
    }
  }

  return output;
}

void example1() {
  vector<int> input = {9, 12, 5, 10, 14, 3, 10};
  vector<int> output = {9, 5, 3, 10, 10, 12, 14};
  assert(pivotArray(input, 10) == output);
}

void example2() {
  vector<int> input = {-3, 4, 3, 2};
  vector<int> output = {-3, 2, 4, 3};
  assert(pivotArray(input, 2) == output);
}

int main() {
  example1();
  example2();
}
