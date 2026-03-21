#include <assert.h>

int magicalString(int n) {
  char s[n + 1];

  for (int i = 0, j = 0; i < n; ++j) {
    // Every other run should be of different char
    const char c = j % 2 ? '2' : '1';
    s[i++] = c;

    // If there's a two, we need to have two identical chars in total
    if (s[j] == '2') {
      s[i++] = c;
    }
  }

  // Substract the amount of 2's from the total amount
  int sum = n;
  for (int i = 0; i < n; ++i) {
    sum -= s[i] - '1';
  }

  return sum;
}

int main(void) {
  assert(magicalString(6) == 3);
  assert(magicalString(1) == 1);
}
