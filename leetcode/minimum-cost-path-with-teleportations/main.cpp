#include <cassert>
#include <climits>
#include <queue>

using namespace std;

vector<pair<int, int>> getTeleports(const vector<vector<int>> &grid,
                                    const size_t i, const size_t j) {
  const size_t height = grid.size();
  const size_t width = grid[0].size();
  const int cost = grid[i][j];
  vector<pair<int, int>> teleports;

  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      // Don't add the current tile
      if (y == i && x == j) {
        continue;
      }

      // Don't move to any tile that is further away
      // from the goal position in both axis
      if (y < i && x < j) {
        continue;
      }

      // Don't add any tile that has a larger cost
      if (cost < grid[y][x]) {
        continue;
      }

      teleports.emplace_back(y, x);
    }
  }

  return teleports;
}

int minCost(const vector<vector<int>> &grid, const int k) {
  const size_t height = grid.size();
  const size_t width = grid[0].size();

  vector<vector<vector<int>>> cache(
      height, vector<vector<int>>(width, vector<int>(k + 1, INT_MAX)));
  queue<tuple<size_t, size_t, int, bool, int>> que;
  que.emplace(0, 0, 0, true, k);

  while (!que.empty()) {
    auto [i, j, cost, teleported, k] = que.front();
    que.pop();

    // Only take the cost of the current tile into account
    // if we haven't moved to it by teleporting
    cost += !teleported * grid[i][j];

    // If a better run exists, abort
    if (cache[i][j][k] <= cost) {
      continue;
    } else {
      cache[i][j][k] = cost;
    }

    // Abort if we're at the bottom right-most tile, which is the goal tile
    if (i == height - 1 && j == width - 1) {
      continue;
    }

    // Add potential teleports to the queue
    if (0 < k) {
      for (const auto &[y, x] : getTeleports(grid, i, j)) {
        que.emplace(y, x, cost, true, k - 1);
      }
    }

    // Add the manual movements to the queue
    if (i + 1 < height) {
      que.emplace(i + 1, j, cost, false, k);
    }
    if (j + 1 < width) {
      que.emplace(i, j + 1, cost, false, k);
    }
  }

  const vector<int> &goalCosts = cache[height - 1][width - 1];
  const int minCost = *min_element(goalCosts.begin(), goalCosts.end());

  return minCost;
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

void example6() {
  vector<vector<int>> input = {
      {229, 161, 256, 264, 185, 303, 277, 202, 269, 280, 211, 14, 126, 180, 57,
       298, 95, 62, 50},
      {329, 237, 133, 93, 312, 77, 294, 213, 75, 96, 77, 263, 95, 236, 339, 164,
       144, 85, 276},
      {175, 73, 91, 90, 368, 251, 279, 239, 356, 332, 312, 236, 146, 139, 180,
       247, 77, 142, 119},
      {221, 222, 142, 191, 293, 296, 252, 277, 296, 215, 297, 206, 336, 263,
       330, 384, 240, 220, 100},
      {216, 218, 329, 293, 265, 153, 179, 402, 281, 185, 350, 397, 302, 389,
       168, 350, 313, 148, 197},
      {460, 429, 163, 435, 334, 351, 373, 202, 161, 167, 438, 444, 202, 352,
       440, 354, 303, 417, 353},
      {309, 428, 484, 398, 280, 297, 412, 305, 321, 290, 210, 276, 418, 247,
       272, 234, 220, 433, 195},
      {360, 443, 366, 403, 249, 294, 279, 486, 350, 464, 418, 288, 375, 379,
       307, 355, 458, 286, 234},
      {379, 252, 381, 332, 358, 410, 498, 317, 361, 290, 326, 544, 417, 494,
       528, 300, 486, 373, 555},
      {418, 473, 296, 401, 487, 554, 279, 421, 454, 516, 551, 441, 559, 453,
       478, 374, 485, 454, 374},
      {453, 490, 530, 564, 462, 586, 585, 596, 330, 520, 575, 547, 391, 596,
       539, 483, 328, 468, 394},
      {542, 631, 581, 417, 562, 472, 484, 599, 536, 644, 461, 419, 408, 461,
       437, 626, 460, 555, 389},
      {526, 503, 449, 582, 449, 548, 438, 407, 676, 450, 471, 428, 589, 389,
       471, 408, 412, 387, 528},
      {539, 657, 660, 695, 487, 696, 561, 453, 614, 665, 603, 682, 636, 486,
       626, 667, 702, 481, 604},
      {679, 585, 533, 464, 657, 664, 651, 697, 638, 619, 567, 470, 712, 683,
       441, 735, 655, 677, 669},
      {555, 556, 701, 605, 512, 599, 725, 502, 696, 535, 720, 520, 731, 747,
       682, 714, 646, 504, 678},
      {720, 667, 729, 699, 563, 787, 547, 628, 533, 517, 689, 620, 588, 602,
       517, 627, 622, 521, 723},
      {789, 542, 606, 801, 817, 557, 675, 786, 707, 788, 783, 610, 772, 614,
       832, 582, 703, 754, 830},
      {685, 744, 603, 781, 705, 604, 755, 701, 716, 581, 859, 797, 704, 601,
       858, 787, 622, 831, 603},
      {713, 734, 823, 807, 634, 687, 667, 847, 697, 761, 624, 822, 601, 615,
       777, 837, 634, 745, 800},
      {669, 811, 751, 907, 629, 840, 646, 626, 679, 743, 754, 715, 655, 837,
       758, 679, 768, 916, 654},
      {730, 753, 719, 885, 819, 679, 877, 766, 729, 757, 740, 906, 842, 785,
       785, 839, 752, 828, 912},
      {756, 799, 722, 938, 722, 784, 724, 778, 856, 851, 898, 760, 798, 708,
       890, 806, 903, 906, 977},
      {764, 737, 892, 766, 936, 754, 995, 915, 854, 807, 884, 750, 815, 919,
       903, 866, 995, 924, 1054}};
  assert(minCost(input, 8) == 3183);
}

int main() {
  example1();
  example2();
  example3();
  example4();
  example5();
  example6();
}
