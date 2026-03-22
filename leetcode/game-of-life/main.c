#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int max(const int a, const int b) { return a > b ? a : b; }

int min(const int a, const int b) { return a < b ? a : b; }

void gameOfLife(int **board, int boardSize, int *boardColSize) {
  int neighbors[boardSize][boardColSize[0]];
  for (int y = 0; y < boardSize; ++y) {
    for (int x = 0; x < boardColSize[y]; ++x) {
      neighbors[y][x] = 0;

      // Get the amount of neighbors for this pixel
      // Also check that we are within boundaries
      for (int i = max(y - 1, 0); i < min(y + 2, boardSize); ++i) {
        for (int j = max(x - 1, 0); j < min(x + 2, boardColSize[i]); ++j) {
          // Don't count yourself as a neighbor
          if (i == y && j == x) {
            continue;
          }

          neighbors[y][x] += board[i][j];
        }
      }
    }
  }

  // Modify the actual board with the gathered information about neighbors
  for (int y = 0; y < boardSize; ++y) {
    for (int x = 0; x < boardColSize[y]; ++x) {
      if (board[y][x] == 0) {
        // Dead cells become alive if there are 3 neighbors
        board[y][x] = neighbors[y][x] == 3;
      } else {
        // Alive cells only stay alive if there are 2 or 3 neighbors
        board[y][x] = neighbors[y][x] == 2 || neighbors[y][x] == 3;
      }
    }
  }
}

void createBoard(const int rows, const int columns, int ***board,
                 int **boardColSize, const int board_temp[rows][columns]) {
  *board = malloc(rows * sizeof(int *));
  *boardColSize = malloc(rows * sizeof(int));

  for (int i = 0; i < rows; ++i) {
    // Allocate memory for each row of the board
    (*board)[i] = malloc(columns * sizeof(int));
    // Copy each row from the array to the pointer array
    memcpy((*board)[i], board_temp[i], columns * sizeof(int));
    // Copy the length of each row to each index of boardColSize
    (*boardColSize)[i] = columns;
  }
}

void freeBoard(int **board, int *boardColSize) {
  for (int i = 0; i < boardColSize[0]; ++i) {
    free(board[i]);
  }
  free(board);
  free(boardColSize);
}

bool equals(int **a, int **b, int boardSize, int *boardColSize) {
  for (int y = 0; y < boardSize; ++y) {
    for (int x = 0; x < boardColSize[y]; ++x) {
      if (a[y][x] != b[y][x]) {
        return false;
      }
    }
  }

  return true;
}

int main(void) {
  // First example, what a mess
  int **board1 = NULL;
  int *boardColSize1 = NULL;
  const int board_temp1[4][3] = {{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}};
  createBoard(4, 3, &board1, &boardColSize1, board_temp1);

  int **board_correct1 = NULL;
  int *boardColSize_correct1 = NULL;
  const int board_correct_temp1[4][3] = {
      {0, 0, 0}, {1, 0, 1}, {0, 1, 1}, {0, 1, 0}};
  createBoard(4, 3, &board_correct1, &boardColSize_correct1,
              board_correct_temp1);

  gameOfLife(board1, 4, boardColSize1);
  assert(equals(board1, board_correct1, 4, boardColSize1));

  freeBoard(board1, boardColSize1);
  freeBoard(board_correct1, boardColSize_correct1);

  // Second example
  int **board2 = NULL;
  int *boardColSize2 = NULL;
  const int board_temp2[2][2] = {{1, 1}, {1, 0}};
  createBoard(2, 2, &board2, &boardColSize2, board_temp2);

  int **board_correct2 = NULL;
  int *boardColSize_correct2 = NULL;
  const int board_correct_temp2[2][2] = {{1, 1}, {1, 1}};
  createBoard(2, 2, &board_correct2, &boardColSize_correct2,
              board_correct_temp2);

  gameOfLife(board2, 2, boardColSize2);
  assert(equals(board2, board_correct2, 2, boardColSize2));

  freeBoard(board2, boardColSize2);
  freeBoard(board_correct2, boardColSize_correct2);
}
