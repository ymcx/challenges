// https://www.geeksforgeeks.org/c/queue-in-c/

#define MAX_SIZE 128

typedef struct {
  int y;
  int x;
} Pair;

typedef struct {
  Pair items[MAX_SIZE];
  int front;
  int rear;
} Queue;

void initializeQueue(Queue *q) {
  q->front = -1;
  q->rear = 0;
}

int isEmpty(Queue *q) { return (q->front == q->rear - 1); }

int isFull(Queue *q) { return (q->rear == MAX_SIZE); }

void enqueue(Queue *q, Pair value) {
  if (isFull(q)) {
    return;
  }
  q->items[q->rear] = value;
  q->rear++;
}

void dequeue(Queue *q) {
  if (isEmpty(q)) {
    return;
  }
  q->front++;
}

Pair peek(Queue *q) {
  if (isEmpty(q)) {
    Pair pair = {0, 0};
    return pair;
  }
  return q->items[q->front + 1];
}
