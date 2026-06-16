#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *addChar(const char *input, const char c) {
  const size_t length = strlen(input);
  char *output = malloc(length + 2);

  memcpy(output, input, length);
  output[length] = c;
  output[length + 1] = '\0';

  return output;
}

char *dupStr(const char *input) {
  const size_t length = strlen(input);
  if (length == 0) {
    return "";
  }

  char *output = malloc(length * 2 + 1);

  memcpy(output, input, length);
  memcpy(output + length, input, length);
  output[length * 2] = '\0';

  return output;
}

char *revStr(const char *input) {
  const size_t length = strlen(input);
  if (length == 0) {
    return "";
  }

  char *output = malloc(length + 1);

  for (size_t i = 0; i < length; ++i) {
    const char c = input[length - i - 1];
    output[i] = c;
  }
  output[length] = '\0';

  return output;
}

char *delChar(const char *input) {
  const size_t length = strlen(input);
  if (length == 0) {
    return "";
  }

  char *output = malloc(length);

  memcpy(output, input, length - 1);
  output[length - 1] = '\0';

  return output;
}

char *processStr(const char *s) {
  const size_t length = strlen(s);
  char *result = "";

  for (size_t i = 0; i < length; ++i) {
    const char c = s[i];

    if (islower(c)) {
      result = addChar(result, c);
    } else if (c == '*') {
      result = delChar(result);
    } else if (c == '#') {
      result = dupStr(result);
    } else if (c == '%') {
      result = revStr(result);
    }
  }

  return result;
}

void example1(void) { assert(!strcmp(processStr("a#b%*"), "ba")); }

void example2(void) { assert(!strcmp(processStr("z*#"), "")); }

void example3(void) { assert(!strcmp(processStr("*%"), "")); }

int main(void) {
  // example1();
  // example2();
  example3();
}
