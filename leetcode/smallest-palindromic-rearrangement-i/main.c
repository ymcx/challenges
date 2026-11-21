#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void *a, const void *b) {
  const char x = *(const char *)a;
  const char y = *(const char *)b;
  return y < x;
}

char *smallestPalindrome(char *s) {
  const size_t n = strlen(s);
  char *result = malloc(sizeof(*result) * (n + 1));
  result[n] = '\0';

  memcpy(result, s, (n + 1) / 2);
  qsort(result, n / 2, sizeof(*result), comp);
  for (size_t i = 0; i < n / 2; ++i) {
    result[n - i - 1] = result[i];
  }

  return result;
}

void example1(void) {
  char *result = smallestPalindrome("z");
  assert(!strcmp(result, "z"));
  free(result);
}

void example2(void) {
  char *result = smallestPalindrome("babab");
  assert(!strcmp(result, "abbba"));
  free(result);
}

void example3(void) {
  char *result = smallestPalindrome("daccad");
  assert(!strcmp(result, "acddca"));
  free(result);
}

void example4(void) {
  char *result = smallestPalindrome("yey");
  assert(!strcmp(result, "yey"));
  free(result);
}

int main(void) {
  example1();
  example2();
  example3();
  example4();
}
