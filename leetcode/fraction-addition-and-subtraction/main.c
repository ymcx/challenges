#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int numerator;
  int denominator;
  bool negative;
} Value;

Value extract_value(const char *expression, const int start, const int end) {
  int i = start;
  while (i < end) {
    if (expression[i] == '/') {
      break;
    }
    ++i;
  }

  const bool negative = start != 0 && expression[start - 1] == '-';
  int n;
  char *str;

  n = i - start;
  str = malloc(sizeof(*str) * (n + 1));
  strncpy(str, expression + start, n);
  str[n] = '\0';
  const int numerator = atoi(str);
  free(str);

  ++i;

  n = end - i;
  str = malloc(sizeof(*str) * (n + 1));
  strncpy(str, expression + i, n);
  str[n] = '\0';
  const int denominator = atoi(str);
  free(str);

  return (Value){numerator, denominator, negative};
}

Value *extract_values(const char *expression, int *v_dst) {
  const size_t n = strlen(expression);

  Value *values = malloc(sizeof(*values) * (n / 3));
  int v = 0;

  int i = 0;
  int start = 0;
  while (i < n) {
    if (i == 0 && expression[i] == '-') {
      start = i + 1;
    } else if (expression[i] == '+' || expression[i] == '-') {
      values[v++] = extract_value(expression, start, i);
      start = i + 1;
    }
    ++i;
  }
  values[v++] = extract_value(expression, start, i);

  *v_dst = v;

  return values;
}

char *fractionAddition(const char *expression) {
  int v = 0;
  Value *values = extract_values(expression, &v);

  for (int i = 0; i < v; ++i) {
    Value a = values[i];
    printf("%b %d/%d\n", a.negative, a.numerator, a.denominator);
  }

  free(values);

  return "";
}

void example1(void) { assert(!strcmp(fractionAddition("-1/2+1/2"), "0/1")); }

void example2(void) {
  assert(!strcmp(fractionAddition("-1/2+1/2+1/3"), "1/3"));
}

void example3(void) { assert(!strcmp(fractionAddition("1/3-1/2"), "-1/6")); }

int main(void) {
  example1();
  example2();
  example3();
}
