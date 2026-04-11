#include <algorithm>
#include <cassert>
#include <cctype>
#include <stack>
#include <string>
#include <vector>

using namespace std;

long evaluate(const string &input) {
  stack<long> st;
  long num = 0;
  char op = '+';

  for (size_t i = 0; i < input.size(); ++i) {
    const char &c = input[i];

    if (isdigit(c)) {
      num *= 10;
      num += c - '0';
    }

    if (!isdigit(c) || i == input.size() - 1) {
      switch (op) {
      case '+':
        st.push(num);
        break;
      case '-':
        st.push(-num);
        break;
      case '*':
        const long top = st.top();
        st.pop();
        st.push(top * num);
        break;
      }

      op = c;
      num = 0;
    }
  }

  long result = 0;
  while (!st.empty()) {
    result += st.top();
    st.pop();
  }

  return result;
}

tuple<string, vector<int>> addSlots(const string &input) {
  vector<int> positions;
  string output = input;

  for (size_t i = 1; i < output.length(); i += 2) {
    output.insert(i, "|");
    positions.push_back(i);
  }

  return {output, positions};
}

vector<string> getAllPossibilities(const string &input) {
  const vector<char> operators = {'*', '+', '-', '|'};
  const auto &[first, positions] = addSlots(input);
  vector<string> strings = {first};

  for (const int i : positions) {
    vector<string> next;
    for (const string &str : strings) {
      for (const char &op : operators) {
        string tmp = str;
        tmp[i] = op;
        next.push_back(tmp);
      }
    }

    strings = next;
  }

  return strings;
}

bool noLeadingZeros(const string &str) {
  bool lastChar = true;
  bool lastCharZero = false;

  for (const char &c : str) {
    if (lastCharZero && isdigit(c)) {
      return false;
    }

    lastCharZero = lastChar && c == '0';
    lastChar = !isdigit(c);
  }

  return true;
}

vector<string> deleteImpossible(const vector<string> &input,
                                const long target) {
  vector<string> output;

  for (string str : input) {
    str.erase(remove(str.begin(), str.end(), '|'), str.end());
    if (noLeadingZeros(str) && evaluate(str) == target) {
      output.push_back(str);
    }
  }

  return output;
}

vector<string> addOperators(string num, long target) {
  const vector<string> strings = getAllPossibilities(num);
  return deleteImpossible(strings, target);
}

int main() {
  assert(addOperators("123", 6) == vector<string>({"1*2*3", "1+2+3"}));
  assert(addOperators("232", 8) == vector<string>({"2*3+2", "2+3*2"}));
  assert(addOperators("3456237490", 9191) == vector<string>({}));
}
