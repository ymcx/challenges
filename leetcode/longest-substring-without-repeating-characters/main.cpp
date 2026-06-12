#include <algorithm>
#include <cassert>
#include <string>
#include <unordered_map>

using namespace std;

int lengthOfLongestSubstring(const string &s) {
  unordered_map<char, size_t> seen;
  size_t start = 0;
  size_t best = 0;

  for (size_t i = 0; i < s.size(); ++i) {
    char c = s[i];
    if (seen.count(c)) {
      start = max(start, seen[c] + 1);
    }

    best = max(best, i - start + 1);
    seen[c] = i;
  }

  return best;
}

int main() {
  assert(lengthOfLongestSubstring("abcabcbb") == 3);
  assert(lengthOfLongestSubstring("bbbbb") == 1);
  assert(lengthOfLongestSubstring("pwwkew") == 3);
}
