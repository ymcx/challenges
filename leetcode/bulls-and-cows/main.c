#include <assert.h>
#include <stdio.h>
#include <string.h>

char *getHint(char *secret, char *guess) {
  int bulls = 0;
  int cows = 0;
  int numbers[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  // Fill numbers with the frequency of each number in secret, skipping those
  // that are bulls
  const int length = strlen(secret);
  for (int i = 0; i != length; ++i) {
    if (secret[i] == guess[i]) {
      continue;
    }

    const int number = secret[i] - '0';
    ++numbers[number];
  }

  // Fill bulls and cows
  for (int i = 0; i != length; ++i) {
    // Increment bulls if exact match is found,
    if (secret[i] == guess[i]) {
      ++bulls;
      continue;
    }

    const int number = guess[i] - '0';
    if (numbers[number] == 0) {
      continue;
    }

    // Increment cows if secret has a matching unused value
    --numbers[number];
    ++cows;
  }

  char *result;
  asprintf(&result, "%dA%dB", bulls, cows);
  return result;
}

int main(void) {
  assert(strcmp(getHint("1807", "7810"), "1A3B") == 0);
  assert(strcmp(getHint("1123", "0111"), "1A1B") == 0);
}
