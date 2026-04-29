#include <cassert>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void reorderList(ListNode *head) {
  ListNode *last = head;
  ListNode *slast = head;

  while (last->next != nullptr) {
    slast = last;
    last = last->next;
  }

  if (slast == head) {
    return;
  }

  last->next = head->next;
  slast->next = nullptr;
  head->next = last;

  reorderList(last->next);
}

ListNode *createListNode(const vector<int> &input) {
  ListNode *node = new ListNode(input[input.size() - 1]);
  for (int i = input.size() - 2; i >= 0; --i) {
    node = new ListNode(input[i], node);
  }

  return node;
}

bool equalsListNode(ListNode *a, ListNode *b) {
  while (a != nullptr && b != nullptr && a->val == b->val) {
    a = a->next;
    b = b->next;
  }

  return a == nullptr && b == nullptr;
}

int main() {
  ListNode *input1 = createListNode({1, 2, 3, 4});
  ListNode *output1 = createListNode({1, 4, 2, 3});

  ListNode *input2 = createListNode({1, 2, 3, 4, 5});
  ListNode *output2 = createListNode({1, 5, 2, 4, 3});

  reorderList(input1);
  reorderList(input2);

  assert(equalsListNode(input1, output1));
  assert(equalsListNode(input2, output2));
}
