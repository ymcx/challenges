#include <algorithm>
#include <cassert>
#include <climits>
#include <ranges>
#include <vector>

using namespace std;

int earliestFinishTimeCondition(vector<int> &startTime1, vector<int> &duration1,
                                vector<int> &startTime2,
                                vector<int> &duration2) {
  int min1 = INT_MAX;
  int min2 = INT_MAX;

  for (const auto &&[s, d] : views::zip(startTime1, duration1)) {
    min1 = min(min1, s + d);
  }

  for (const auto &&[s, d] : views::zip(startTime2, duration2)) {
    min2 = min(min2, max(s, min1) + d);
  }

  return min2;
}

int earliestFinishTime(vector<int> &landStartTime, vector<int> &landDuration,
                       vector<int> &waterStartTime,
                       vector<int> &waterDuration) {
  int land_first = earliestFinishTimeCondition(landStartTime, landDuration,
                                               waterStartTime, waterDuration);
  int water_first = earliestFinishTimeCondition(waterStartTime, waterDuration,
                                                landStartTime, landDuration);

  return min(land_first, water_first);
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
