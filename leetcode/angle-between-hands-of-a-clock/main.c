#include <assert.h>
#include <math.h>

double min(const double a, const double b) { return a < b ? a : b; }

double angleClock(const double hour, const double minutes) {
  const double angleMinutes = minutes * 6.0;       // [0, 360]

  double angleHours = hour * 30.0 + minutes / 2.0; // [0, 360 + 30]
  if (angleHours > 360.0) {
    angleHours -= 360.0;
  }

  const double a = fabs(angleHours - angleMinutes);
  const double b = 360.0 - a;

  return min(a, b);
}

void example1(void) { assert(angleClock(12, 30) == 165.0); }

void example2(void) { assert(angleClock(3, 30) == 75.0); }

void example3(void) { assert(angleClock(3, 15) == 7.5); }

void example4(void) { assert(angleClock(12, 0) == 0.0); }

void example5(void) { assert(angleClock(6, 5) == 152.5); }

void example6(void) { assert(angleClock(1, 57) == 76.5); }

int main(void) {
  example1();
  example2();
  example3();
  example4();
  example5();
  example6();
}
