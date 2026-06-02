#include <algorithm>
#include <cassert>
#include <climits>
#include <ranges>
#include <vector>

using namespace std;

int earliestFinishTime(vector<int> &landStartTime, vector<int> &landDuration,
                       vector<int> &waterStartTime,
                       vector<int> &waterDuration) {
  int lowest = INT_MAX;
  for (const auto &&[s1, d1] : views::zip(landStartTime, landDuration)) {
    for (const auto &&[s2, d2] : views::zip(waterStartTime, waterDuration)) {
      lowest = min(lowest, max(s1 + d1, s2) + d2);
    }
  }

  for (const auto &&[s1, d1] : views::zip(waterStartTime, waterDuration)) {
    for (const auto &&[s2, d2] : views::zip(landStartTime, landDuration)) {
      lowest = min(lowest, max(s1 + d1, s2) + d2);
    }
  }

  return lowest;
}

void example1() {
  vector<int> landStartTime = {2, 8};
  vector<int> landDuration = {4, 1};
  vector<int> waterStartTime = {6};
  vector<int> waterDuration = {3};
  assert(earliestFinishTime(landStartTime, landDuration, waterStartTime,
                            waterDuration) == 9);
}

void example2() {
  vector<int> landStartTime = {5};
  vector<int> landDuration = {3};
  vector<int> waterStartTime = {1};
  vector<int> waterDuration = {10};
  assert(earliestFinishTime(landStartTime, landDuration, waterStartTime,
                            waterDuration) == 14);
}

int main() {
  example1();
  example2();
}
