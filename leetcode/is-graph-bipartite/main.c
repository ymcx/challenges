#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int index;
  int part;
} Tuple;

bool isBipartite(int **graph, int graphSize, int *graphColSize) {
  int *partition = malloc(sizeof(*partition) * graphSize);
  memset(partition, -1, sizeof(*partition) * graphSize);

  for (int x = 0; x < graphSize; ++x) {
    if (partition[x] != -1) {
      continue;
    }

    int q = 0;
    Tuple *queue = malloc(sizeof(*queue) * graphSize);
    queue[q++] = (Tuple){x, 0};
    partition[x] = 0;

    while (q != 0) {
      const Tuple tuple = queue[--q];
      const int i = tuple.index;
      const int part = tuple.part;

      for (int j = 0; j < graphColSize[i]; ++j) {
        const int k = graph[i][j];

        if (partition[k] == part) {
          free(partition);
          free(queue);
          return false;
        }

        if (partition[k] != -1) {
          continue;
        }

        partition[k] = part ^ 1;
        queue[q++] = (Tuple){k, part ^ 1};
      }
    }

    free(queue);
  }

  free(partition);
  return true;
}

void example1(void) {
  int *graph[] = {(int[]){1, 2, 3}, (int[]){0, 2}, (int[]){0, 1, 3},
                  (int[]){0, 2}};
  int graphColSize[] = {3, 2, 3, 2};
  assert(!isBipartite(graph, 4, graphColSize));
}

void example2(void) {
  int *graph[] = {(int[]){1, 3}, (int[]){0, 2}, (int[]){1, 3}, (int[]){0, 2}};
  int graphColSize[] = {2, 2, 2, 2};
  assert(isBipartite(graph, 4, graphColSize));
}

void example3(void) {
  int *graph[] = {(int[]){4}, (int[]){}, (int[]){4}, (int[]){4},
                  (int[]){0, 2, 3}};
  int graphColSize[] = {1, 0, 1, 1, 3};
  assert(isBipartite(graph, 5, graphColSize));
}

void example4(void) {
  int *graph[] = {(int[]){},
                  (int[]){2, 4, 6},
                  (int[]){1, 4, 8, 9},
                  (int[]){7, 8},
                  (int[]){1, 2, 8, 9},
                  (int[]){6, 9},
                  (int[]){1, 5, 7, 8, 9},
                  (int[]){3, 6, 9},
                  (int[]){2, 3, 4, 6, 9},
                  (int[]){2, 4, 5, 6, 7, 8}};
  int graphColSize[] = {0, 3, 4, 2, 4, 2, 5, 3, 5, 6};
  assert(!isBipartite(graph, 10, graphColSize));
}

int main(void) {
  example1();
  example2();
  example3();
  example4();
}
