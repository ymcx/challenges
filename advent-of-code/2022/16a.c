#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALVES 128
#define MAX_CONNECTIONS 16
#define INF 1000000

typedef struct {
  int flow;
  int connections[MAX_CONNECTIONS];
  int connectionsSize;
} Valve;

static int name_id(const char *name) {
  return (name[0] - 'A') * 26 + (name[1] - 'A');
}

static int get_valves(Valve *valves, int *valvesSize) {
  static int nameToIndex[26 * 26];
  char line[1024];
  int rawConnections[MAX_VALVES][MAX_CONNECTIONS];
  int rawConnectionsSize[MAX_VALVES];
  int count = 0;

  for (int i = 0; i < 26 * 26; ++i) {
    nameToIndex[i] = -1;
  }

  while (fgets(line, sizeof(line), stdin) != NULL) {
    char name[4];
    int flow;

    if (sscanf(line, "Valve %3s has flow rate=%d", name, &flow) != 2) {
      continue;
    }

    nameToIndex[name_id(name)] = count;
    valves[count].flow = flow;
    rawConnectionsSize[count] = 0;

    char *cursor = strchr(line, ';');
    if (cursor != NULL) {
      cursor = strstr(cursor, "valve");
      if (cursor != NULL) {
        cursor += 5;
        if (*cursor == 's') {
          ++cursor;
        }

        while (*cursor != '\0') {
          while (*cursor == ' ') {
            ++cursor;
          }
          if (cursor[0] < 'A' || cursor[0] > 'Z' || cursor[1] < 'A' ||
              cursor[1] > 'Z') {
            break;
          }

          rawConnections[count][rawConnectionsSize[count]++] = name_id(cursor);
          cursor += 2;

          if (*cursor == ',') {
            ++cursor;
          } else {
            break;
          }
        }
      }
    }

    ++count;
  }

  for (int i = 0; i < count; ++i) {
    valves[i].connectionsSize = rawConnectionsSize[i];
    for (int j = 0; j < rawConnectionsSize[i]; ++j) {
      valves[i].connections[j] = nameToIndex[rawConnections[i][j]];
    }
  }

  *valvesSize = count;
  return nameToIndex[name_id("AA")];
}

static void floyd_warshall(int valvesSize, int dist[MAX_VALVES][MAX_VALVES],
                           Valve *valves) {
  for (int i = 0; i < valvesSize; ++i) {
    for (int j = 0; j < valvesSize; ++j) {
      dist[i][j] = i == j ? 0 : INF;
    }
  }

  for (int i = 0; i < valvesSize; ++i) {
    for (int j = 0; j < valves[i].connectionsSize; ++j) {
      int c = valves[i].connections[j];
      dist[i][c] = 1;
      dist[c][i] = 1;
    }
  }

  for (int k = 0; k < valvesSize; ++k) {
    for (int i = 0; i < valvesSize; ++i) {
      for (int j = 0; j < valvesSize; ++j) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }
}

typedef struct {
  int positionCount;
  int relevantCount;
  int maskCount;
  int positionValve[MAX_CONNECTIONS + 1];
  int relevantValve[MAX_CONNECTIONS];
  int relevantFlow[MAX_CONNECTIONS];
  int relevantPosition[MAX_CONNECTIONS];
  int dist[MAX_VALVES][MAX_VALVES];
  uint16_t *memo;
} Solver;

static int search(Solver *solver, int position, int time, int mask) {
  size_t index =
      (((size_t)time * solver->positionCount + position) * solver->maskCount) +
      mask;
  uint16_t *memo = &solver->memo[index];

  if (*memo != UINT16_MAX) {
    return *memo;
  }

  int best = 0;

  for (int i = 0; i < solver->relevantCount; ++i) {
    if (mask & (1 << i)) {
      continue;
    }

    int valve = solver->relevantValve[i];
    int remaining =
        time - solver->dist[solver->positionValve[position]][valve] - 1;
    if (remaining <= 0) {
      continue;
    }

    int reward =
        remaining * solver->relevantFlow[i] +
        search(solver, solver->relevantPosition[i], remaining, mask | (1 << i));
    if (reward > best) {
      best = reward;
    }
  }

  *memo = (uint16_t)best;
  return best;
}

int main(void) {
  Valve valves[MAX_VALVES];
  int valvesSize = 0;
  int start = get_valves(valves, &valvesSize);

  static int dist[MAX_VALVES][MAX_VALVES];
  floyd_warshall(valvesSize, dist, valves);

  Solver solver;
  memset(&solver, 0, sizeof(solver));
  memcpy(solver.dist, dist, sizeof(dist));

  int startInRelevant = 0;

  for (int i = 0; i < valvesSize; ++i) {
    if (valves[i].flow > 0) {
      if (i == start) {
        startInRelevant = 1;
      }
      solver.relevantValve[solver.relevantCount] = i;
      solver.relevantFlow[solver.relevantCount] = valves[i].flow;
      ++solver.relevantCount;
    }
  }

  solver.positionCount = solver.relevantCount + (startInRelevant ? 0 : 1);
  if (!startInRelevant) {
    solver.positionValve[0] = start;
  }

  for (int i = 0; i < solver.relevantCount; ++i) {
    int position = i + (startInRelevant ? 0 : 1);
    solver.relevantPosition[i] = position;
    solver.positionValve[position] = solver.relevantValve[i];
  }

  solver.maskCount = 1 << solver.relevantCount;
  size_t memoSize = (size_t)31 * solver.positionCount * solver.maskCount;
  solver.memo = malloc(memoSize * sizeof(*solver.memo));
  if (solver.memo == NULL) {
    fprintf(stderr, "out of memory\n");
    return 1;
  }
  memset(solver.memo, 0xFF, memoSize * sizeof(*solver.memo));

  int startPosition = 0;
  for (int i = 0; i < solver.relevantCount; ++i) {
    if (solver.relevantValve[i] == start) {
      startPosition = solver.relevantPosition[i];
      break;
    }
  }

  printf("%d\n", search(&solver, startPosition, 30, 0));

  free(solver.memo);
  return 0;
}
