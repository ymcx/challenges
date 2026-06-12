#include <cassert>
#include <cmath>
#include <functional>
#include <queue>
#include <unordered_set>
#include <utility>

using namespace std;

struct Hash {
  size_t operator()(const pair<int, int> &pair) const {
    const int a = hash<int>{}(get<0>(pair)) << 0;
    const int b = hash<int>{}(get<1>(pair)) << 1;
    return a ^ b;
  }
};

int getScore(const long resultMin, const long resultMax) {
  const long result = max(resultMin, resultMax);
  const long modulo = pow(10, 9) + 7;

  return max(-1L, result % modulo);
}

int maxProductPath(const vector<vector<int>> &grid) {
  const int height = grid.size();
  const int width = grid[0].size();

  unordered_map<pair<int, int>, pair<long, long>, Hash> cache;
  queue<tuple<int, int, long, unordered_set<pair<int, int>, Hash>>> que;
  que.push({0, 0, 1, {}});

  while (!que.empty()) {
    auto [y, x, score, path] = que.front();
    que.pop();

    // Out-of-bounds
    if (y < 0 || x < 0 || y >= height || x >= width) {
      continue;
    }

    // We've already been at y,x during this run
    if (path.contains({y, x})) {
      continue;
    } else {
      path.emplace(y, x);
    }

    score *= grid[y][x];

    if (cache.contains({y, x})) {
      const auto [cacheMin, cacheMax] = cache[{y, x}];

      // A better pair of runs exists in the cache, abort
      if (cacheMin <= score && score <= cacheMax) {
        continue;
      }

      // The current run is better than either of the cached runs at this
      // coordinate
      cache[{y, x}] = {min(cacheMin, score), max(cacheMax, score)};
    } else {
      cache[{y, x}] = {score, score};
    }

    // We're at the goal coordinates
    if (y == height - 1 && x == width - 1) {
      continue;
    }

    que.emplace(y + 1, x, score, path);
    que.emplace(y, x + 1, score, path);
  }

  const auto [cacheMin, cacheMax] = cache[{height - 1, width - 1}];
  return getScore(cacheMin, cacheMax);
}

void example1() {
  const vector<vector<int>> input = {{-1, -2, -3}, {-2, -3, -3}, {-3, -3, -2}};
  assert(maxProductPath(input) == -1);
}

void example2() {
  const vector<vector<int>> input = {{1, -2, 1}, {1, -2, 1}, {3, -4, 1}};
  assert(maxProductPath(input) == 8);
}

void example3() {
  const vector<vector<int>> input = {{1, 3}, {0, -4}};
  assert(maxProductPath(input) == 0);
}

int main() {
  example1();
  example2();
  example3();
}
