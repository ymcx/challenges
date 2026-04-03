#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int prefixConnected(vector<string> &words, int k) {
  unordered_map<string, int> frequency;
  int result = 0;

  for (const string &word : words) {
    if (word.size() < (size_t)k) {
      continue;
    }

    const string prefix = word.substr(0, k);
    result += ++frequency[prefix] == 2;
  }

  return result;
}

int main() {
  vector<string> input1 = {"apple", "apply", "banana", "bandit"};
  vector<string> input2 = {"car", "cat", "cartoon"};
  vector<string> input3 = {"bat", "dog", "dog", "doggy", "bat"};

  assert(prefixConnected(input1, 2) == 2);
  assert(prefixConnected(input2, 3) == 1);
  assert(prefixConnected(input3, 3) == 2);
}
