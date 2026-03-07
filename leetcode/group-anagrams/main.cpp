#include <algorithm>
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string> &strs) {
  unordered_map<string, vector<string>> anagrams_map;

  for (const auto &str : strs) {
    string str_sorted = str;
    sort(str_sorted.begin(), str_sorted.end());
    anagrams_map[str_sorted].push_back(str);
  }

  vector<vector<string>> anagrams(anagrams_map.size());
  transform(anagrams_map.begin(), anagrams_map.end(), anagrams.begin(),
            [](auto i) { return i.second; });

  for (auto &i : anagrams) {
    sort(i.begin(), i.end());
  }

  return anagrams;
}

int main() {
  vector<string> input1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
  vector<string> input2 = {""};
  vector<string> input3 = {"a"};
  vector<vector<string>> output1 = {
      {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}};
  vector<vector<string>> output2 = {{""}};
  vector<vector<string>> output3 = {{"a"}};

  assert(groupAnagrams(input1) == output1);
  assert(groupAnagrams(input2) == output2);
  assert(groupAnagrams(input3) == output3);
}
