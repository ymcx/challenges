#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

int factorial(int x) {
  int result = 1;
  for (int i = 2; i <= x; ++i) {
    result *= i;
  }

  return result;
}

string vectorToString(vector<int> &input) {
  string output;
  for (const int &i : input) {
    output += to_string(i);
  }

  return output;
}

string getPermutation(int n, int k) {
  // The first element should be 0 instead of 1
  --k;

  // The length of the run consisting of the values that share the first number
  int group_length = factorial(n) / n;

  // Groups should use one based indexing
  int group = k / group_length + 1;
  vector<int> permutation = {group};

  while (1 < n) {
    // The sub-permutation consists of n-m items
    // when conditioning on the previous m items
    --n;

    // Map k to the new length
    k %= group_length;
    group_length = factorial(n) / n;
    group = k / group_length + 1;

    // We'll need to account for previous values
    // in the permutation since no duplicates are allowed
    vector<int> permutation_sorted(permutation.size());
    partial_sort_copy(permutation.begin(), permutation.end(),
                      permutation_sorted.begin(), permutation_sorted.end());
    for (const int &group_old : permutation_sorted) {
      group += group_old <= group;
    }

    permutation.push_back(group);
  }

  return vectorToString(permutation);
}

int main() {
  assert(getPermutation(3, 3) == "213");
  assert(getPermutation(4, 9) == "2314");
  assert(getPermutation(3, 1) == "123");
}
