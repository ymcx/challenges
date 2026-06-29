#include <cassert>
#include <climits>
#include <vector>

using namespace std;

int earliestFinishTime(vector<int> &landStartTime, vector<int> &landDuration,
                       vector<int> &waterStartTime,
                       vector<int> &waterDuration) {
  int lowest = INT_MAX;

  for (size_t i = 0; i < landStartTime.size(); ++i) {
    const int s1 = landStartTime[i];
    const int d1 = landDuration[i];

    for (size_t j = 0; j < waterStartTime.size(); ++j) {
      const int s2 = waterStartTime[j];
      const int d2 = waterDuration[j];

      lowest = min(lowest, max(s1 + d1, s2) + d2);
    }
  }

  for (size_t i = 0; i < waterStartTime.size(); ++i) {
    const int s1 = waterStartTime[i];
    const int d1 = waterDuration[i];

    for (size_t j = 0; j < landStartTime.size(); ++j) {
      const int s2 = landStartTime[j];
      const int d2 = landDuration[j];

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
