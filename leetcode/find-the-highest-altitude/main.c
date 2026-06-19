#include <assert.h>

int largestAltitude(const int *gain, const int gainSize) {
  int sum = 0;
  int result = 0;

  for (int i = 0; i < gainSize; ++i) {
    sum += gain[i];
    if (result < sum) {
      result = sum;
    }
  }

  return result;
}

void example1(void) {
  int input[] = {-5, 1, 5, 0, -7};
  assert(largestAltitude(input, 5) == 1);
}

void example2(void) {
  int input[] = {-4, -3, -2, -1, 4, 3, 2};
  assert(largestAltitude(input, 7) == 0);
}

int main(void) {
  example1();
  example2();
}
