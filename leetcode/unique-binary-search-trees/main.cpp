#include <cassert>

using namespace std;

__float128 factorial(int u, int l = 2) {
  __float128 result = 1;
  for (int i = l; i <= u; ++i) {
    result *= i;
  }

  return result;
}

int numTrees(int n) { return factorial(2 * n, n + 2) / factorial(n); }

int main() {
  assert(numTrees(1) == 1);
  assert(numTrees(3) == 5);
}
