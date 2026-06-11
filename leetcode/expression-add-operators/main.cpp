#include <algorithm>
#include <cassert>
#include <cctype>
#include <stack>
#include <string>
#include <vector>

using namespace std;

bool evaluate(const vector<char> &input, const long target) {
  stack<long> st;
  long num = 0;
  char op = '+';

  for (size_t i = 0; i < input.size(); ++i) {
    const char &c = input[i];

    // Skip temporary padding
    if (c == '|') {
      continue;
    }

    // It's a digit so add it to the buffer
    if (isdigit(c)) {
      num = num * 10 + c - '0';
    }

    // We're either at a sign or at the end of the equation, use the buffer
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

  return result == target;
}

vector<int> addSlots(vector<char> &input) {
  vector<int> positions;
  for (size_t i = 1; i < input.size(); i += 2) {
    input.insert(input.begin() + i, ' ');
    positions.push_back(i);
  }

  return positions;
}

bool leadingZeros(const vector<char> &str) {
  char c1, c2, c3;
  for (size_t i = 1; i < str.size(); ++i) {
    if (i != 1) {
      c1 = str[i - 2];
    }
    c2 = str[i - 1];
    c3 = str[i - 0];

    // The first char is out-of-bounds or one of the signs
    const bool first = i == 1 || c1 == '-' || c1 == '+' || c1 == '*';

    // The second char is zero
    const bool second = c2 == '0';

    // The third char is a digit (padded with a |)
    const bool third = c3 == '|';

    // Matches strings such as 1+01+1 and 01+1
    if (first && second && third) {
      return true;
    }
  }

  return false;
}

vector<vector<char>> getAllPossibilities(vector<char> &input,
                                         const long target) {
  const vector<char> operators = {'*', '+', '-', '|'};
  const vector<int> positions = addSlots(input);
  vector<vector<char>> strings = {input};

  for (size_t i = 0; i < positions.size(); ++i) {
    const int position = positions[i];
    vector<vector<char>> next;

    for (vector<char> &str : strings) {
      for (const char op : operators) {
        str[position] = op;

        // If the string contains leading zeros, skip
        if (leadingZeros(str)) {
          continue;
        }

        // Only verify the string once we're at the last padding position
        if (i == positions.size() - 1 && !evaluate(str, target)) {
          continue;
        }

        next.push_back(str);
      }
    }

    strings = next;
  }

  return strings;
}

vector<string> addOperators(const string &num, const long target) {
  vector<char> numVector(num.begin(), num.end());
  vector<vector<char>> stringsVector = getAllPossibilities(numVector, target);

  // Remove padding & convert to string
  vector<string> strings;
  for (vector<char> &strVector : stringsVector) {
    strVector.erase(remove(strVector.begin(), strVector.end(), '|'),
                    strVector.end());
    const string str(strVector.begin(), strVector.end());
    strings.push_back(str);
  }

  return strings;
}

int main() {
  assert(addOperators("123", 6) == vector<string>({"1*2*3", "1+2+3"}));
  assert(addOperators("232", 8) == vector<string>({"2*3+2", "2+3*2"}));
  assert(addOperators("3456237490", 9191) == vector<string>({}));
  assert(addOperators("105", 5) == vector<string>({"1*0+5", "10-5"}));
  assert(addOperators("2147483647", 2147483647) ==
         vector<string>({"2147483647"}));
  assert(addOperators("00", 0) == vector<string>({"0*0", "0+0", "0-0"}));
}
