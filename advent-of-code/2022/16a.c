#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int flow;
  int *connections;
  int connectionsSize;
} Valve;

int get_valve(const char *str) { return (str[0] - 'A') * 26 + str[1] - 'A'; }

int get_flow(const char *str) { return strtol(str, NULL, 10); }

int *get_connections(const char *str, int *connectionsSize) {
  const int padding = str[0] == ' ';
  const int n = (strlen(str) - padding + 1) / 4;
  *connectionsSize = n;
  int *connections = malloc(sizeof(*connections) * n);

  for (int c = 0; c < n; ++c) {
    connections[c] = get_valve(str + padding + c * 4);
  }

  return connections;
}

Valve *get_valves(int *valvesSize) {
  char line[1024];
  const int n = 676;
  *valvesSize = n;
  Valve *valves = calloc(n, sizeof(*valves));

  while (fgets(line, sizeof(line), stdin) != NULL) {
    const int valve = get_valve(line + 6);
    const int flow = get_flow(line + 23);
    int connectionsSize = 0;
    int *connections = get_connections(line + 49, &connectionsSize);
    valves[valve] = (Valve){flow, connections, connectionsSize};
  }

  return valves;
}

int path_cost(const Valve *valves, const int valvesSize, const int curr,
              const int last) {
  int *dist = malloc(sizeof(*dist) * valvesSize);
  int *queue = malloc(sizeof(*queue) * valvesSize);

  for (int i = 0; i < valvesSize; ++i) {
    dist[i] = -1;
  }

  int head = 0;
  int tail = 0;

  dist[curr] = 0;
  queue[tail++] = curr;

  while (head < tail) {
    const int current = queue[head++];

    if (current == last) {
      break;
    }

    for (int i = 0; i < valves[current].connectionsSize; ++i) {
      const int next = valves[current].connections[i];

      if (dist[next] != -1) {
        continue;
      }

      dist[next] = dist[current] + 1;
      queue[tail++] = next;
    }
  }

  const int result = dist[last];

  free(dist);
  free(queue);

  return result;
}

int solve(Valve *valves, const int valvesSize) {
  int time = 30;
  int result = 0;
  int curr = 0;

  while (time > 0) {
    int best_valve = 0;
    int best_travel = 0;
    int best_score = 0;

    for (int next = 0; next < valvesSize; ++next) {
      if (valves[next].connections == NULL || next == curr) {
        continue;
      }

      const int travel = path_cost(valves, valvesSize, curr, next);
      const int score = valves[next].flow * (time - travel - 1);
      if (score > best_score) {
        best_score = score;
        best_travel = travel;
        best_valve = next;
      }
    }

    if (best_score <= 0) {
      break;
    }

    result += best_score;
    valves[best_valve].flow = 0;
    curr = best_valve;
    time -= best_travel + 1;
  }

  return result;
}

int main() {
  int valvesSize = 0;
  Valve *valves = get_valves(&valvesSize);

  const int result = solve(valves, valvesSize);
  printf("%d\n", result);

  for (int i = 0; i < valvesSize; ++i) {
    if (valves[i].connections != NULL) {
      free(valves[i].connections);
    }
  }
  free(valves);
}
