#include <cassert>
#include <cmath>

using namespace std;

int get_digit(const int number, const int i) {
  int n = floor(log10(number));
  int divider = pow(10, n - i);
  int digit = (number / divider) % 10;

  return digit;
}

int totalWaviness(int num1, int num2) {
  int waviness = 0;

  for (int number = num1; number <= num2; ++number) {
    for (int i = 2; i < floor(log10(number)) + 1; ++i) {
      const int digit_last = get_digit(number, i - 2);
      const int digit_cur = get_digit(number, i - 1);
      const int digit_next = get_digit(number, i);

      waviness += (digit_last < digit_cur && digit_next < digit_cur) ||
                  (digit_last > digit_cur && digit_next > digit_cur);
    }
  }

  return waviness;
}

void example1() { assert(totalWaviness(120, 130) == 3); }

void example2() { assert(totalWaviness(198, 202) == 3); }

void example3() { assert(totalWaviness(4848, 4848) == 2); }

int main() {
  example1();
  example2();
  example3();
}
