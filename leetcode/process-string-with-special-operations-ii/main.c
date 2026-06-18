#include <assert.h>
#include <string.h>

size_t getTotalLength(const char *s) {
  size_t lengthOriginal = strlen(s);
  size_t lengthTotal = 0;

  for (size_t i = 0; i < lengthOriginal; ++i) {
    const char c = s[i];
    switch (c) {
    case '%':
      continue;
    case '#':
      lengthTotal *= 2;
      continue;
    case '*':
      if (lengthTotal <= 0) {
        continue;
      }
      lengthTotal -= 1;
      continue;
    default:
      lengthTotal += 1;
      continue;
    }
  }

  return lengthTotal;
}

char processStr(const char *s, size_t k) {
  size_t length = getTotalLength(s);

  if (length <= k) {
    return '.';
  }

  for (int i = strlen(s) - 1; i >= 0; --i) {
    const char c = s[i];
    switch (c) {
    case '%':
      k = length - k - 1;
      continue;
    case '#':
      length /= 2;
      k %= length;
      continue;
    case '*':
      length += 1;
      continue;
    default:
      length -= 1;
      if (k == length) {
        return c;
      }
      continue;
    }
  }

  return '.';
}

void example1(void) { assert(processStr("a#b%*", 1) == 'a'); }

void example2(void) { assert(processStr("cd%#*#", 3) == 'd'); }

void example3(void) { assert(processStr("z*#", 0) == '.'); }

void example4(void) { assert(processStr("%#*gm#xib", 2) == 'g'); }

int main(void) {
  example1();
  example2();
  example3();
  example4();
}
