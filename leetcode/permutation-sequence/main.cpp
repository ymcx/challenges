// TODO: fix getPermutation(3, 2) == "132"

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
  --k;

  int length = factorial(n) / n;
  int number = k / length + 1;
  vector<int> numbers = {number};

  for (int i = n - 1; i > 0; --i) {
    k %= length;
    length /= i;
    number = k / length + 1;

    while (find(numbers.begin(), numbers.end(), number) != numbers.end()) {
      ++number;
    }

    numbers.push_back(number);
  }

  return vectorToString(numbers);
}

int main() {
  assert(getPermutation(3, 3) == "213");
  assert(getPermutation(4, 9) == "2314");
  assert(getPermutation(3, 1) == "123");
}
