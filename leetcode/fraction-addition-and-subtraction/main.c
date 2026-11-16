#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int numerator;
  int denominator;
} Value;

Value extract_value(const char *expression, const int start, const int end) {
  int i = start;
  while (i < end && expression[i] != '/') {
    ++i;
  }

  const bool negative = start != 0 && expression[start - 1] == '-';
  int n;
  char *str;

  n = i - start;
  str = malloc(sizeof(*str) * (n + 1));
  strncpy(str, expression + start, n);
  str[n] = '\0';
  const int numerator = atoi(str) * (negative ? -1 : 1);
  free(str);

  n = end - i - 1;
  str = malloc(sizeof(*str) * (n + 1));
  strncpy(str, expression + i + 1, n);
  str[n] = '\0';
  const int denominator = atoi(str);
  free(str);

  return (Value){numerator, denominator};
}

Value *extract_values(const char *expression, int *v_dst) {
  const size_t n = strlen(expression);

  Value *values = malloc(sizeof(*values) * (n / 3));
  int v = 0;

  int i = 0;
  int start = 0;
  while (i < n) {
    if (expression[i] == '+' || expression[i] == '-') {
      if (i != 0) {
        values[v++] = extract_value(expression, start, i);
      }
      start = i + 1;
    }
    ++i;
  }
  values[v++] = extract_value(expression, start, i);

  *v_dst = v;

  return values;
}

// https://www.geeksforgeeks.org/dsa/program-to-find-gcd-or-hcf-of-two-numbers/
int gcd(const int a, const int b) {
  if (a == 0 || b == 0) {
    return a > b ? a : b;
  }

  int result = a < b ? a : b;
  while (result > 0 && (a % result != 0 || b % result != 0)) {
    --result;
  }

  return result;
}

int digit_count(const int n) {
  if (n == 0) {
    return 1;
  }

  const bool negative = n < 0;
  return (negative ? 1 : 0) + log10(abs(n)) + 1;
}

int get_denominator(const Value *values, const int v) {
  int result = values[0].denominator;
  for (int i = 1; i < v; ++i) {
    const int right = values[i].denominator;
    result = (result * right) / gcd(result, right);
  }

  return result;
}

int get_numerator(const int denominator, const Value *values, const int v) {
  int result = 0;
  for (int i = 0; i < v; ++i) {
    const int n = values[i].numerator;
    const int d = values[i].denominator;
    result += (denominator / d) * n;
  }

  return result;
}

char *fractionAddition(const char *expression) {
  int v = 0;
  Value *values = extract_values(expression, &v);

  int denominator = get_denominator(values, v);
  int numerator = get_numerator(denominator, values, v);

  free(values);

  const int d = gcd(denominator, abs(numerator));
  denominator /= d;
  numerator /= d;

  const int digits_numerator = digit_count(numerator);
  const int digits_denominator = digit_count(denominator);
  const int n = digits_numerator + 1 + digits_denominator;
  char *result = malloc(sizeof(*result) * (n + 1));

  sprintf(result, "%d", numerator);
  sprintf(result + digits_numerator + 1, "%d", denominator);
  result[digits_numerator] = '/';
  result[n] = '\0';

  return result;
}

void example1(void) {
  assert(strcmp(fractionAddition("-1/2+1/2"), "0/1") == 0);
}

void example2(void) {
  assert(strcmp(fractionAddition("-1/2+1/2+1/3"), "1/3") == 0);
}

void example3(void) {
  assert(strcmp(fractionAddition("1/3-1/2"), "-1/6") == 0);
}

void example4(void) {
  assert(strcmp(fractionAddition("-4/7-3/4+2/3"), "-55/84") == 0);
}

int main(void) {
  example1();
  example2();
  example3();
  example4();
}
