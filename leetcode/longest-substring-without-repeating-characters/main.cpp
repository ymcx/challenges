#include <algorithm>
#include <cassert>
#include <string>
#include <unordered_map>

using namespace std;

size_t get_length(string input) {
  unordered_map<char, size_t> seen;
  size_t start = 0;
  size_t best = 0;

  for (size_t i = 0; i < input.size(); ++i) {
    char c = input[i];
    if (seen.count(c)) {
      start = max(start, seen[c] + 1);
    }

    best = max(best, i - start + 1);
    seen[c] = i;
  }

  return best;
}

int main() {
  assert(get_length("abcabcbb") == 3);
  assert(get_length("bbbbb") == 1);
  assert(get_length("pwwkew") == 3);
}
