#include <cassert>
#include <cstdint>

using namespace std;

int32_t reverse(int32_t x) {
  int64_t result = 0;

  while (true) {
    result += x % 10;
    x /= 10;

    if (x == 0) {
      break;
    }

    result *= 10;
  }

  if (result < INT32_MIN || INT32_MAX < result) {
    return 0;
  }

  return result;
}

int main() {
  assert(reverse(123) == 321);
  assert(reverse(-123) == -321);
  assert(reverse(120) == 21);
}
