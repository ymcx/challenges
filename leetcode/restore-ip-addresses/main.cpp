#include <cassert>
#include <initializer_list>
#include <string>
#include <vector>

using namespace std;

vector<string> restoreIpAddresses(string str, int iteration = 0) {
  if (iteration == 3) {
    if ((str != "0" && str.starts_with('0')) || str.size() < 1 ||
        3 < str.size()) {
      return {};
    }

    return {str};
  }

  vector<string> strs;
  for (size_t length = 1; length < 4; ++length) {
    string left = str.substr(0, length);
    if ((left != "0" && left.starts_with('0')) || 255 < stoi(left) ||
        str.size() <= length) {
      break;
    }

    string str_next = str.substr(length);
    for (const string &right : restoreIpAddresses(str_next, iteration + 1)) {
      strs.push_back(left + "." + right);
    }
  }

  return strs;
}

int main() {
  vector<string> output1 = {"255.255.11.135", "255.255.111.35"};
  vector<string> output2 = {"0.0.0.0"};
  vector<string> output3 = {"1.0.10.23", "1.0.102.3", "10.1.0.23", "10.10.2.3",
                            "101.0.2.3"};

  assert(restoreIpAddresses("25525511135") == output1);
  assert(restoreIpAddresses("0000") == output2);
  assert(restoreIpAddresses("101023") == output3);
}
