#include <map>
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

typedef map<pair<int, int>, vector<TreeNode *>> Memo;

// https://leetcode.com/problems/unique-binary-search-trees-ii/editorial/
vector<TreeNode *> allPossibleBST(const int start, const int end, Memo &memo) {
  if (start > end) {
    return {nullptr};
  }

  if (memo.find({start, end}) != memo.end()) {
    return memo[{start, end}];
  }

  vector<TreeNode *> result;
  for (int i = start; i <= end; ++i) {
    const vector<TreeNode *> leftTrees = allPossibleBST(start, i - 1, memo);
    const vector<TreeNode *> rightTrees = allPossibleBST(i + 1, end, memo);

    for (TreeNode *left : leftTrees) {
      for (TreeNode *right : rightTrees) {
        TreeNode *root = new TreeNode(i, left, right);
        result.push_back(root);
      }
    }
  }

  memo[{start, end}] = result;
  return result;
}

vector<TreeNode *> generateTrees(int n) {
  Memo memo;
  return allPossibleBST(1, n, memo);
}

int main() {}
