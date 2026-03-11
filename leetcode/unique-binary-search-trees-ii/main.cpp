#include <cassert>
#include <deque>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

vector<TreeNode *> createTree(vector<vector<int>> items_all) {
  vector<TreeNode *> trees;

  for (const vector<int> &items : items_all) {
    TreeNode *child_l = nullptr;
    TreeNode *child_r = nullptr;

    for (int i = items.size() - 1; 0 <= i; i -= 2) {
      const int &value_l = items[i - 1];
      const int &value_r = items[i];

      child_l =
          value_l != -1 ? new TreeNode(value_l, child_l, child_r) : nullptr;
      child_r =
          value_r != -1 ? new TreeNode(value_r, child_r, child_l) : nullptr;
    }

    trees.push_back(child_l);
  }

  return trees;
}

vector<TreeNode *> generateTrees(int n) {}

bool equals(vector<TreeNode *> a, vector<TreeNode *> b) {
  for (size_t i = 0; i < a.size(); ++i) {
    TreeNode *node_a = a[i];
    TreeNode *node_b = b[i];

    tuple<TreeNode *, TreeNode *> tuplee = {node_a, node_b};
    deque<tuple<TreeNode *, TreeNode *>> queue = {tuplee};
    while (!queue.empty()) {
      auto [na, nb] = queue.back();
      queue.pop_back();

      if (na == nullptr && nb == nullptr) {
        continue;
      }

      if (na == nullptr xor nb == nullptr) {
        return false;
      }

      if (na->val != nb->val) {
        return false;
      }

      queue.emplace_back(na->left, nb->left);
      queue.emplace_back(na->right, nb->right);
    }
  }

  return true;
}

int main() {
  vector<vector<int>> tree = {{{1, -1, 2, -1, 3, -1},
                               {1, -1, 3, 2},
                               {2, 1, 3, -1},
                               {3, 1, -1, -1, 2, -1},
                               {3, 2, -1, 1}}};
  assert(equals(generateTrees(3), createTree(tree)));
}
