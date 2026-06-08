#include <algorithm>
#include <bitset>
#include <cassert>
#include <vector>

using namespace std;

static bool comp(const int a, const int b) {
  const bitset abin = bitset<14>(a);
  const bitset bbin = bitset<14>(b);

  // Same amount of bits, sort using the original ints
  if (abin.count() == bbin.count()) {
    return a < b;
  }

  // Different amount of bits, sort using the binary view
  return abin.count() < bbin.count();
}

vector<int> sortByBits(vector<int> &arr) {
  sort(arr.begin(), arr.end(), comp);
  return arr;
}

void example1() {
  vector<int> input = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> output = {0, 1, 2, 4, 8, 3, 5, 6, 7};
  assert(sortByBits(input) == output);
}

void example2() {
  vector<int> input = {1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};
  vector<int> output = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
  assert(sortByBits(input) == output);
}

int main() {
  example1();
  example2();
}
