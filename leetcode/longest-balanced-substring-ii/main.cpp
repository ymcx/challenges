#include <algorithm>
#include <cassert>
#include <string>
#include <unordered_map>

using namespace std;

int sum(const unordered_map<char, int> &charAmount) {
  int sum = 0;
  for (const auto &[_, amount] : charAmount) {
    sum += amount;
  }

  return sum;
}

bool isBalanced(const unordered_map<char, int> &charAmount) {
  const int target = charAmount.begin()->second;
  for (const auto &[_, amount] : charAmount) {
    if (target != amount) {
      return false;
    }
  }

  return true;
}

int longestBalanced(string s) {
  int maxLength = 1;
  for (size_t pos = 0; pos < s.size() - 1; ++pos) {
    unordered_map<char, int> charAmount;

    for (size_t i = pos; i < s.size(); ++i) {
      const char c = s[i];
      ++charAmount[c];

      if (isBalanced(charAmount)) {
        maxLength = max(maxLength, sum(charAmount));
      }
    }
  }

  return maxLength;
}

void example1() { assert(longestBalanced("abbac") == 4); }

void example2() { assert(longestBalanced("aabcc") == 3); }

void example3() { assert(longestBalanced("aba") == 2); }

void example4() {
  assert(
      longestBalanced(
          "aaabacbaabcaabacaccbaabcbbcccbbbbcacacbbcbacccacbcbcccabcbccbacbbcaa"
          "bccaaacababcaccaccccccacccbbbcbaabbccacabbacacbcbbcbbbbbacbbaaacbcbb"
          "bacabccbcbaaabaaaaabcbccbabbbcaabcacbbbccaaacbccccbabbcacbcaabcabaca"
          "bbbacbacbccccbababbbbccccaabbacabbbbcbbbabcaabbababcbcaacabbcbbaccbb"
          "ccbbccccccaaaaccaaaacacabccacbcccccbbacabccaacbbaacbaabaccbbaabacbbc"
          "bcacccbabccaccabacbbaaacaacbacccaccccbbacbbccabcccbcabbcbaaa") ==
      90);
}

void example5() {
  assert(longestBalanced(
             "acbacbcbbccbcccbbcccbcaabcaabacabacaabccaacacbcbbaacaaabccbcbbcca"
             "bcbcaabbcacacbabaacabbbacaabbbabccabcabbabcbcbbacccbcbbabacaacbbb"
             "bacaabbbbbcaccbcacacccccababacabcabbaccaaabccaacaaabaacbcccccbaca"
             "bacbccabbabacbbcbcbbacbabacaabbbcacaacaabacaacabcbacbaaacccccaccb"
             "abccbabacacbaabcccbcbbcbacaabcbcacabaabaccaacaabcccbcbabccbaaaabc"
             "bcbcbacababcccbbccbbacbbcabbccbaacbaababccbccbacaabcccbabbbcaccac"
             "accbabcaacaccbbbabbbaacbccababcabcbcbbbabaccbbbacccababcaccbbbbaa"
             "cacbcababaaabaacbabbaccccbbcccbbcbbcbcbacabcabcacbabbacbccbbcaccc"
             "cbbbbaabbcaaacaacbbabbabcbacbacbaaccaacaccccacabbbbbcacaccacacbaa"
             "bbabaabbcacabaaacbbcbaacbbbababccbccbaacaabacabbbaccbbcbacacacbba"
             "abbabbcabbbacabbccbcccbcacbacabbccaacabccbbbacbacabaa") == 216);
}

int main() {
  example1();
  example2();
  example3();
  example4();
  example5();
}
