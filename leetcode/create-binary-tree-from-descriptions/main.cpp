#include <cassert>
#include <optional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
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

TreeNode *createBinaryTree(vector<vector<int>> &descriptions) {
  unordered_map<int, tuple<TreeNode *, TreeNode *, TreeNode *>> tree;
  unordered_set<int> parents;
  unordered_set<int> children;

  // Build a hashmap with the nodes along with their children
  // Additionally take note of each parent and children
  while (!descriptions.empty()) {
    const vector<int> &description = descriptions.back();
    const int parent = description[0];
    const int child = description[1];
    const int isLeft = description[2];
    descriptions.pop_back();

    parents.insert(parent);
    children.insert(child);

    if (!tree.contains(parent)) {
      TreeNode *parentNode = new TreeNode(parent);
      tree[parent] = {parentNode, nullptr, nullptr};
    }
    if (!tree.contains(child)) {
      TreeNode *childNode = new TreeNode(child);
      tree[child] = {childNode, nullptr, nullptr};
    }

    TreeNode *childNode = get<0>(tree[child]);
    if (isLeft) {
      get<1>(tree[parent]) = childNode;
    } else {
      get<2>(tree[parent]) = childNode;
    }
  }

  // Connect the nodes to each other via the hashmap
  for (auto iterator = tree.begin(); iterator != tree.end(); ++iterator) {
    auto &[parentNode, leftNode, rightNode] = iterator->second;
    parentNode->left = leftNode;
    parentNode->right = rightNode;
  }

  // Find the root node and return it
  // The root is a parent, but it isn't anyone's child
  for (const auto parent : parents) {
    if (!children.contains(parent)) {
      TreeNode *rootNode = get<0>(tree[parent]);
      return rootNode;
    }
  }

  return new TreeNode();
}

vector<optional<int>> toVector(const TreeNode *node) {
  vector<optional<int>> output;
  queue<const TreeNode *> que;
  que.push(node);

  while (!que.empty()) {
    const TreeNode *node = que.front();
    que.pop();

    // If the child doesn't exist, add a placeholder
    if (!node) {
      output.push_back(nullopt);
      continue;
    }

    output.push_back(node->val);
    que.push(node->left);
    que.push(node->right);
  }

  // Trim the vector from the back, since it has unnecessary nullopts
  while (!output.back()) {
    output.pop_back();
  }

  return output;
}

void example1() {
  vector<vector<int>> input = {
      {20, 15, 1}, {20, 17, 0}, {50, 20, 1}, {50, 80, 0}, {80, 19, 1}};
  vector<optional<int>> output = {50, 20, 80, 15, 17, 19};
  assert(toVector(createBinaryTree(input)) == output);
}

void example2() {
  vector<vector<int>> input = {{1, 2, 1}, {2, 3, 0}, {3, 4, 1}};
  vector<optional<int>> output = {1, 2, nullopt, nullopt, 3, 4};
  assert(toVector(createBinaryTree(input)) == output);
}

int main() {
  example1();
  example2();
}
