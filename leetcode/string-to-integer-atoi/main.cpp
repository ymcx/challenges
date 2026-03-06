#include <cassert>
#include <cstdint>
#include <regex>
#include <string>

using namespace std;

int myAtoi(string s) {
  int64_t result = 0;
  s = regex_replace(s, regex("^ *"), "");
  int multiplier = (s.empty() || s[0] != '-') ? 1 : -1;
  s = regex_replace(s, regex("^[+-]?0*"), "");

  for (char c : s) {
    if (!isdigit(c)) {
      break;
    }

    result *= 10;
    result += c - '0';

    if (multiplier * result < INT32_MIN || INT32_MAX < multiplier * result) {
      return (multiplier == 1) ? INT32_MAX : INT32_MIN;
    }
  }

  return multiplier * result;
}

int main() {
  assert(myAtoi("42") == 42);
  assert(myAtoi(" -042") == -42);
  assert(myAtoi("1337c0d3") == 1337);
  assert(myAtoi("0-1") == 0);
  assert(myAtoi("words and 987") == 0);
}
