#include <assert.h>
#include <string.h>

int numOfStrings(char **patterns, int patternsSize, char *word) {
  int result = 0;

  for (int i = 0; i < patternsSize; ++i) {
    result += strstr(word, patterns[i]) != NULL;
  }

  return result;
}

void example1(void) {
  char *input[] = {"a", "abc", "bc", "d"};
  assert(numOfStrings(input, 4, "abc") == 3);
}

void example2(void) {
  char *input[] = {"a", "b", "c"};
  assert(numOfStrings(input, 3, "aaaaabbbbb") == 2);
}

void example3(void) {
  char *input[] = {"a", "a", "a"};
  assert(numOfStrings(input, 3, "ab") == 3);
}

int main(void) {
  example1();
  example2();
  example3();
}
