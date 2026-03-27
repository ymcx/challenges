#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <stack>
#include <string>
#include <tuple>

using namespace std;

tuple<int, int> findMatchingBrackets(const string &s) {
  stack<int> brackets;

  for (size_t i = 0; i < s.length(); ++i) {
    switch (s[i]) {
    case '[':
      brackets.push(i);
      break;
    case ']':
      if (brackets.size() == 1) {
        return tuple(brackets.top(), i);
      }

      brackets.pop();
      break;
    }
  }

  return tuple(-1, -1);
}

string repeatString(const string &s, const int n) {
  string result;
  result.reserve(s.length() * n);

  for (int i = 0; i < n; ++i) {
    result += s;
  }

  return result;
}

int getIntegersBefore(const string &s, const int end) {
  int start = end;
  while (0 < start && isdigit(s[start - 1])) {
    --start;
  }

  const string result = s.substr(start, end - start);
  return stoi(result);
}

string decodeString(string s) {
  while (s.contains('[')) {
    const auto [i, j] = findMatchingBrackets(s);
    const int repeat_n = getIntegersBefore(s, i);
    const int repeat_n_length = 1 + log(repeat_n) / log(10);
    const string repeat_string = s.substr(i + 1, j - i - 1);

    s = s.substr(0, i - repeat_n_length) +
        repeatString(repeat_string, repeat_n) + s.substr(j + 1);
  }

  return s;
}

int main() {
  assert(decodeString("3[a]2[bc]") == "aaabcbc");
  assert(decodeString("3[a2[c]]") == "accaccacc");
  assert(decodeString("2[abc]3[cd]ef") == "abcabccdcdcdef");
}
