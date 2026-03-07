#include <cassert>
#include <unordered_set>
#include <vector>

using namespace std;

bool isValidStraight(vector<vector<char>> &board, bool rows) {
  for (int x = 0; x < 9; ++x) {
    unordered_set<char> seen;
    for (int y = 0; y < 9; ++y) {
      char item = rows ? board[x][y] : board[y][x];
      if (item == '.') {
        continue;
      }

      if (seen.count(item)) {
        return false;
      }

      seen.insert(item);
    }
  }

  return true;
}

bool isValidRows(vector<vector<char>> &board) {
  return isValidStraight(board, true);
}

bool isValidColumns(vector<vector<char>> &board) {
  return isValidStraight(board, false);
}

bool isValidSquares(vector<vector<char>> &board) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      unordered_set<char> seen;
      for (int x = i * 3; x < i * 3 + 3; ++x) {
        for (int y = j * 3; y < j * 3 + 3; ++y) {
          char item = board[x][y];
          if (item == '.') {
            continue;
          }

          if (seen.count(item)) {
            return false;
          }

          seen.insert(item);
        }
      }
    }
  }

  return true;
}

bool isValidSudoku(vector<vector<char>> &board) {
  return isValidRows(board) && isValidColumns(board) && isValidSquares(board);
}

int main() {
  vector<vector<char>> input1 = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                 {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                 {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                 {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                 {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                 {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                 {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                 {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                 {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  vector<vector<char>> input2 = {{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
                                 {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                 {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                 {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                 {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                 {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                 {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                 {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                 {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  assert(isValidSudoku(input1) == true);
  assert(isValidSudoku(input2) == false);
}
