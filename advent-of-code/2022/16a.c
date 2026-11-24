#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int flow;
  int *connections;
  size_t connectionsSize;
} Valve;

int get_valve(const char *str) { return (str[0] - 'A') * 26 + str[1] - 'A'; }

int get_flow(const char *str) { return strtol(str, NULL, 10); }

int *get_connections(const char *str, size_t *connectionsSize) {
  const size_t padding = str[0] == ' ';
  const size_t n = (strlen(str) - padding + 1) / 4;
  *connectionsSize = n;
  int *connections = malloc(sizeof(*connections) * n);

  for (size_t c = 0; c < n; ++c) {
    connections[c] = get_valve(str + padding + c * 4);
  }

  return connections;
}

Valve *get_valves(size_t *valvesSize) {
  char line[1024];
  Valve *valves = malloc(sizeof(*valves) * 676);

  while (fgets(line, sizeof(line), stdin) != NULL) {
    const int valve = get_valve(line + 6);
    const int flow = get_flow(line + 23);
    size_t connectionsSize = 0;
    int *connections = get_connections(line + 49, &connectionsSize);
    valves[valve] = (Valve){flow, connections, connectionsSize};
  }

  return valves;
}

int main() {
  size_t valvesSize = 0;
  Valve *valves = get_valves(&valvesSize);
}
