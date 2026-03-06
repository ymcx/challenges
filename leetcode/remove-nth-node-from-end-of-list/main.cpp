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

ListNode *removeNthFromEnd(ListNode *head, int n) {
  ListNode *head_front = head;
  ListNode *head_back = head_front;

  for (int i = 0; i < n; ++i) {
    head_front = head_front->next;
  }

  if (head_front == nullptr) {
    ListNode *head_back_next = head_back->next;
    head_back->val = 0;
    head_back->next = nullptr;
    return head_back_next;
  }

  while (head_front->next != nullptr) {
    head_front = head_front->next;
    head_back = head_back->next;
  }

  head_back->next = head_back->next->next;

  return head;
}

ListNode *createListNode(vector<int> values) {
  if (values.empty()) {
    return nullptr;
  }

  int i = values.size() - 1;
  ListNode *node = new ListNode(values[i]);
  --i;

  while (i >= 0) {
    node = new ListNode(values[i], node);
    --i;
  }

  return node;
}

bool equals(ListNode *a, ListNode *b) {
  while (a != nullptr && b != nullptr) {
    if (a->val != b->val) {
      return false;
    }

    a = a->next;
    b = b->next;
  }

  return a == nullptr && b == nullptr;
}

int main() {
  ListNode *input1 = createListNode({1, 2, 3, 4, 5});
  ListNode *input2 = createListNode({1});
  ListNode *input3 = createListNode({1, 2});
  ListNode *output1 = createListNode({1, 2, 3, 5});
  ListNode *output2 = createListNode({});
  ListNode *output3 = createListNode({1});

  assert(equals(removeNthFromEnd(input1, 2), output1));
  assert(equals(removeNthFromEnd(input2, 1), output2));
  assert(equals(removeNthFromEnd(input3, 1), output3));
}
