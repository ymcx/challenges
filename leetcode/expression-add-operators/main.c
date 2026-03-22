#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(char **results, int *results_index, const char *temp1) {
  results[*results_index] = malloc(100 * sizeof(char));
  strcpy(results[*results_index], temp1);
  ++(*results_index);
}

void getResults(const int sum, const char *input, const int answer_correct,
                char **results, const char *result, int *results_index) {
  char *first = malloc(strlen(input) + 1);
  strcpy(first, input);
  const char *input_next = input;

  for (size_t i = 1; i <= strlen(input); ++i) {
    char *result_left = malloc(strlen(result) + 1);
    char *result_right = malloc(strlen(result) + 1);
    strcpy(result_left, result);
    strcpy(result_right, result);

    first[i] = '\0';
    ++input_next;

    if (result[0] != '\0') {
      strcat(result_left, "*");
      strcat(result_right, "+");
    }
    strcat(result_left, first);
    strcat(result_right, first);

    int sum_next_left = atoi(first);
    int sum_next_right = atoi(first);
    if (result[0] != '\0') {
      sum_next_left *= sum;
      sum_next_right += sum;
      getResults(sum_next_left, input_next, answer_correct, results,
                 result_left, results_index);
    }
    getResults(sum_next_right, input_next, answer_correct, results,
               result_right, results_index);

    if (strlen(input_next) == 0) {
      if (sum_next_left == answer_correct) {
        add(results, results_index, result_left);
      }
      if (sum_next_right == answer_correct) {
        add(results, results_index, result_right);
      }
    }

    free(result_left);
    free(result_right);
    first[i] = input_next[0];
  }

  free(first);
}

int main(void) {
  const char *input = "2432";
  char **arr = malloc(100 * sizeof(char *));
  int s = 0;

  getResults(0, input, 11, arr, "", &s);

  for (int i = 0; i < 2; ++i) {
    printf("%s\n", arr[i]);
  }
}
