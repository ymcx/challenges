#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

static vector<pair<int, int>> getTeleports(const vector<vector<int>> &grid,
                                           const size_t i, const size_t j) {
  vector<pair<int, int>> teleports;
  for (size_t y = 0; y < grid.size(); ++y) {
    for (size_t x = 0; x < grid[0].size(); ++x) {
      if (y <= i && x <= j) {
        continue;
      }

      if (grid[y][x] <= grid[i][j]) {
        teleports.push_back({y, x});
      }
    }
  }

  return teleports;
}

struct Hash {
  size_t operator()(const tuple<int, int, int> &tuple) const {
    const int a = hash<int>{}(get<0>(tuple)) << 0;
    const int b = hash<int>{}(get<1>(tuple)) << 1;
    const int c = hash<int>{}(get<2>(tuple)) << 2;
    return a ^ b ^ c;
  }
};

static int minCost(const vector<vector<int>> &grid, const int k) {
  const int height = grid.size();
  const int width = grid[0].size();

  int result = INT_MAX;
  unordered_map<tuple<int, int, int>, int, Hash> cache;
  queue<tuple<int, int, int, bool, int>> que;
  que.push({0, 0, 0, true, k});

  while (!que.empty()) {
    auto [i, j, cost, tp, k] = que.front();
    que.pop();

    if (i >= height || j >= width) {
      continue;
    }

    if (!tp) {
      cost += grid[i][j];
    }

    if (i == height - 1 && j == width - 1) {
      result = min(result, cost);
      continue;
    }

    if (cache.contains({i, j, k}) && cache[{i, j, k}] <= cost) {
      continue;
    }
    cache[{i, j, k}] = cost;

    if (k > 0) {
      for (const auto &[y, x] : getTeleports(grid, i, j)) {
        que.push({y, x, cost, true, k - 1});
      }
    }

    que.push({i + 1, j, cost, false, k});
    que.push({i, j + 1, cost, false, k});
  }

  cout << result << endl;

  return result;
}

void example1() {
  vector<vector<int>> input = {{1, 3, 3}, {2, 5, 4}, {4, 3, 5}};
  assert(minCost(input, 2) == 7);
}

void example2() {
  vector<vector<int>> input = {{1, 2}, {2, 3}, {3, 4}};
  assert(minCost(input, 1) == 9);
}

void example3() {
  vector<vector<int>> input = {{3, 1}, {10, 4}};
  assert(minCost(input, 7) == 4);
}

void example4() {
  vector<vector<int>> input = {{19, 10}, {23, 13}, {16, 32},
                               {38, 41}, {30, 36}, {53, 31}};
  assert(minCost(input, 1) == 55);
}

void example5() {
  vector<vector<int>> input = {{3, 0, 0},  {3, 1, 2},   {4, 4, 3},
                               {5, 4, 6},  {8, 6, 4},   {9, 8, 6},
                               {11, 8, 8}, {11, 7, 12}, {12, 10, 9}};
  assert(minCost(input, 6) == 23);
}

int main() {
  example1();
  example2();
  example3();
  example4();
  example5();
}
