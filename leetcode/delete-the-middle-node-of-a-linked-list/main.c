#include <assert.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *deleteMiddle(struct ListNode *head) {
  // The ListNode consists of just one element
  if (head->next == NULL) {
    return NULL;
  }

  struct ListNode *node;

  // Find the amount of elements in the ListNode
  node = head;
  int length = 0;
  while (node != NULL) {
    node = node->next;
    ++length;
  }

  // Go to the element just before the middle element
  node = head;
  for (int i = 0; i < length / 2 - 1; ++i) {
    node = node->next;
  }
  node->next = node->next->next;

  return head;
}

struct ListNode *createListNode(const int array[], const int length) {
  struct ListNode *next = NULL;
  struct ListNode *node = NULL;

  for (int i = length - 1; i >= 0; --i) {
    node = malloc(sizeof(struct ListNode));
    node->val = array[i];
    node->next = next;
    next = node;
  }

  return node;
}

void assertListNode(struct ListNode *a, struct ListNode *b) {
  while (a != NULL && b != NULL) {
    assert(a->val == b->val);

    a = a->next;
    b = b->next;
  }

  assert(a == NULL && b == NULL);
}

void example1(void) {
  const int inputArray[] = {1, 3, 4, 7, 1, 2, 6};
  struct ListNode *input = createListNode(inputArray, 7);

  const int outputArray[] = {1, 3, 4, 1, 2, 6};
  struct ListNode *output = createListNode(outputArray, 6);

  assertListNode(deleteMiddle(input), output);
}

void example2(void) {
  const int inputArray[] = {1, 2, 3, 4};
  struct ListNode *input = createListNode(inputArray, 4);

  const int outputArray[] = {1, 2, 4};
  struct ListNode *output = createListNode(outputArray, 3);

  assertListNode(deleteMiddle(input), output);
}

void example3(void) {
  const int inputArray[] = {2, 1};
  struct ListNode *input = createListNode(inputArray, 2);

  const int outputArray[] = {2};
  struct ListNode *output = createListNode(outputArray, 1);

  assertListNode(deleteMiddle(input), output);
}

void example4(void) {
  const int inputArray[] = {1};
  struct ListNode *input = createListNode(inputArray, 1);

  struct ListNode *output = createListNode(NULL, 0);

  assertListNode(deleteMiddle(input), output);
}

int main(void) {
  example1();
  example2();
  example3();
  example4();
}
