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

ListNode *rotateRight(ListNode *head, int k) {
  if (k == 0 || head == nullptr) {
    return head;
  }

  // Connect tail to head
  int length = 1;
  ListNode *head_back = head;
  while (head_back->next != nullptr) {
    head_back = head_back->next;
    ++length;
  }
  head_back->next = head;

  // Disconnect from new position
  for (int i = 0; i < length - k % length; ++i) {
    head = head->next;
    head_back = head_back->next;
  }
  head_back->next = nullptr;

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
  ListNode *input2 = createListNode({0, 1, 2});
  ListNode *output1 = createListNode({4, 5, 1, 2, 3});
  ListNode *output2 = createListNode({2, 0, 1});

  assert(equals(rotateRight(input1, 2), output1));
  assert(equals(rotateRight(input2, 4), output2));
}
