#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void *a, const void *b) {
  const char *x = *(const char **)a;
  const char *y = *(const char **)b;
  return strcmp(x, y);
}

void equal(char **a, char **b, const int aSize, const int bSize) {
  assert(aSize == bSize);
  for (size_t i = 0; i < aSize; ++i) {
    assert(!strcmp(a[i], b[i]));
  }
}

size_t charAmount(const char *s, const size_t n) {
  size_t result = 0;
  for (size_t i = 0; i < n; ++i) {
    result += isalpha(s[i]) ? 1 : 0;
  }

  return result;
}

char **letterCasePermutation(char *s, int *returnSize) {
  const size_t n = strlen(s);
  const size_t chars = charAmount(s, n);
  *returnSize = 1 << chars; // 2 ** chars
  char **output = malloc(sizeof(*output) * (*returnSize));
  size_t o = 0;

  char *str = malloc(sizeof(*str) * (n + 1));
  for (size_t i = 0; i < n; ++i) {
    str[i] = tolower(s[i]);
  }
  str[n] = '\0';
  output[o++] = str;

  for (size_t i = 0; i < n; ++i) {
    const char c = toupper(s[i]);
    if (isdigit(c)) {
      continue;
    }

    const size_t o_tmp = o;
    for (size_t j = 0; j < o_tmp; ++j) {
      char *str = malloc(sizeof(*str) * (n + 1));
      strcpy(str, output[j]);
      str[i] = c;
      str[n] = '\0';
      output[o++] = str;
    }
  }

  return output;
}

void example1(void) {
  int expectedSize = 4;
  int outputSize = 0;
  char *expected[] = {"a1b2", "a1B2", "A1b2", "A1B2"};
  char **output = letterCasePermutation("a1b2", &outputSize);
  qsort(expected, expectedSize, sizeof(*expected), comp);
  qsort(output, outputSize, sizeof(*output), comp);
  equal(expected, output, expectedSize, outputSize);

  for (size_t i = 0; i < outputSize; ++i) {
    free(output[i]);
  }
  free(output);
}

void example2(void) {
  int expectedSize = 2;
  int outputSize = 0;
  char *expected[] = {"3z4", "3Z4"};
  char **output = letterCasePermutation("3z4", &outputSize);
  qsort(expected, expectedSize, sizeof(*expected), comp);
  qsort(output, outputSize, sizeof(*output), comp);
  equal(expected, output, expectedSize, outputSize);

  for (size_t i = 0; i < outputSize; ++i) {
    free(output[i]);
  }
  free(output);
}

int main(void) {
  example1();
  example2();
}
