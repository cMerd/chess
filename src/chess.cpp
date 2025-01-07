#include <algorithm>
#include <chess.hpp>
#include <utility>
#include <vector>

chess::chess() {
  board.assign(8, std::vector<square>(8, {piece::null, color::null}));
  selected = {-1, -1};
  switcher = {-1, -1};
  isSelected = false;
  switching = false;
  canLightCastle1 = canLightCastle2 = canDarkCastle1 = canDarkCastle2 = true;
  turn = color::light;

  board[0][0] = {piece::rook, color::dark};
  board[0][1] = {piece::knight, color::dark};
  board[0][2] = {piece::bishop, color::dark};
  board[0][3] = {piece::queen, color::dark};
  board[0][4] = {piece::king, color::dark};
  board[0][5] = {piece::bishop, color::dark};
  board[0][6] = {piece::knight, color::dark};
  board[0][7] = {piece::rook, color::dark};

  for (int i = 0; i < 8; i++) {
    board[1][i] = {piece::pawn, color::dark};
  }

  board[7][0] = {piece::rook, color::light};
  board[7][1] = {piece::knight, color::light};
  board[7][2] = {piece::bishop, color::light};
  board[7][3] = {piece::queen, color::light};
  board[7][4] = {piece::king, color::light};
  board[7][5] = {piece::bishop, color::light};
  board[7][6] = {piece::knight, color::light};
  board[7][7] = {piece::rook, color::light};

  for (int i = 0; i < 8; i++) {
    board[6][i] = {piece::pawn, color::light};
  }
}

std::vector<std::pair<int, int>> chess::getMoves(int i, int j) {
  std::vector<std::pair<int, int>> moves;

  switch (board[i][j].type) {
  case piece::null:
    break;
  case piece::pawn:
    if (board[i][j].col == color::light) {
      if (i != 0 and board[i - 1][j].col == color::null) {
        square temp = board[i - 1][j];
        bool didIt = false;
        board[i - 1][j] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(color::light)) {
          moves.emplace_back(i - 1, j);
          didIt = true;
        }

        board[i][j] = board[i - 1][j];
        board[i - 1][j] = temp;

        if (didIt) {
          if (i == 6 and board[i - 2][j].col == color::null) {
            square temp = board[i - 2][j];
            board[i - 2][j] = board[i][j];
            board[i][j] = {piece::null, color::null};

            if (!isInCheck(color::light)) {
              moves.emplace_back(i - 2, j);
            }

            board[i][j] = board[i - 2][j];
            board[i - 2][j] = temp;
          }
        }
      }

      if (i != 0 and j != 0 and board[i - 1][j - 1].col == color::dark) {
        square temp = board[i - 1][j - 1];
        board[i - 1][j - 1] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(color::light)) {
          moves.emplace_back(i - 1, j - 1);
        }

        board[i][j] = board[i - 1][j - 1];
        board[i - 1][j - 1] = temp;
      }

      if (i != 0 and j != 7 and board[i - 1][j + 1].col == color::dark) {
        square temp = board[i - 1][j + 1];
        board[i - 1][j + 1] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(color::light)) {
          moves.emplace_back(i - 1, j + 1);
        }

        board[i][j] = board[i - 1][j + 1];
        board[i - 1][j + 1] = temp;
      }
    } else {
      if (i != 7 and board[i + 1][j].col == color::null) {
        square temp = board[i + 1][j];
        bool didIt = false;
        board[i + 1][j] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(color::dark)) {
          moves.emplace_back(i + 1, j);
          didIt = true;
        }

        board[i][j] = board[i + 1][j];
        board[i + 1][j] = temp;

        if (didIt) {
          if (i == 1 and board[i + 2][j].col == color::null) {
            square temp = board[i + 2][j];
            board[i + 2][j] = board[i][j];
            board[i][j] = {piece::null, color::null};

            if (!isInCheck(color::dark)) {
              moves.emplace_back(i + 2, j);
            }

            board[i][j] = board[i + 2][j];
            board[i + 2][j] = temp;
          }
        }
      }

      if (i != 7 and j != 0 and board[i + 1][j - 1].col == color::light) {
        square temp = board[i + 1][j - 1];
        board[i + 1][j - 1] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(color::dark)) {
          moves.emplace_back(i + 1, j - 1);
        }

        board[i][j] = board[i + 1][j - 1];
        board[i + 1][j - 1] = temp;
      }

      if (i != 7 and j != 7 and board[i + 1][j + 1].col == color::light) {
        square temp = board[i + 1][j + 1];
        board[i + 1][j + 1] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(color::dark)) {
          moves.emplace_back(i + 1, j + 1);
        }

        board[i][j] = board[i + 1][j + 1];
        board[i + 1][j + 1] = temp;
      }
    }

    break;
  case piece::rook:

    for (int x = i + 1; x < 8; x++) {
      if (board[x][j].col == color::null) {
        square temp = board[x][j];
        board[x][j] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[x][j].col)) {
          moves.emplace_back(x, j);
        }

        board[i][j] = board[x][j];
        board[x][j] = temp;
      } else if (board[x][j].col != board[i][j].col) {
        square temp = board[x][j];
        board[x][j] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[x][j].col)) {
          moves.emplace_back(x, j);
        }

        board[i][j] = board[x][j];
        board[x][j] = temp;
        break;
      } else {
        break;
      }
    }

    for (int x = i - 1; x >= 0; x--) {
      if (board[x][j].col == color::null) {
        square temp = board[x][j];
        board[x][j] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[x][j].col)) {
          moves.emplace_back(x, j);
        }

        board[i][j] = board[x][j];
        board[x][j] = temp;
      } else if (board[x][j].col != board[i][j].col) {
        square temp = board[x][j];
        board[x][j] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[x][j].col)) {
          moves.emplace_back(x, j);
        }

        board[i][j] = board[x][j];
        board[x][j] = temp;
        break;
      } else {
        break;
      }
    }

    for (int y = j + 1; y < 8; y++) {
      if (board[i][y].col == color::null) {
        square temp = board[i][y];
        board[i][y] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i][y].col)) {
          moves.emplace_back(i, y);
        }

        board[i][j] = board[i][y];
        board[i][y] = temp;
      } else if (board[i][y].col != board[i][j].col) {
        square temp = board[i][y];
        board[i][y] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i][y].col)) {
          moves.emplace_back(i, y);
        }

        board[i][j] = board[i][y];
        board[i][y] = temp;
        break;
      } else {
        break;
      }
    }

    for (int y = j - 1; y >= 0; y--) {
      if (board[i][y].col == color::null) {
        square temp = board[i][y];
        board[i][y] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i][y].col)) {
          moves.emplace_back(i, y);
        }

        board[i][j] = board[i][y];
        board[i][y] = temp;
      } else if (board[i][y].col != board[i][j].col) {
        square temp = board[i][y];
        board[i][y] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i][y].col)) {
          moves.emplace_back(i, y);
        }

        board[i][j] = board[i][y];
        board[i][y] = temp;
        break;
      } else {
        break;
      }
    }

    break;
  case piece::bishop:

    for (int x = 1; i + x < 8 and j + x < 8; x++) {
      if (board[i + x][j + x].col == color::null) {
        square temp = board[i + x][j + x];
        board[i + x][j + x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i + x][j + x].col)) {
          moves.emplace_back(i + x, j + x);
        }

        board[i][j] = board[i + x][j + x];
        board[i + x][j + x] = temp;
      } else if (board[i + x][j + x].col != board[i][j].col) {
        square temp = board[i + x][j + x];
        board[i + x][j + x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i + x][j + x].col)) {
          moves.emplace_back(i + x, j + x);
        }

        board[i][j] = board[i + x][j + x];
        board[i + x][j + x] = temp;
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i + x < 8 and j - x >= 0; x++) {
      if (board[i + x][j - x].col == color::null) {
        square temp = board[i + x][j - x];
        board[i + x][j - x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i + x][j - x].col)) {
          moves.emplace_back(i + x, j - x);
        }

        board[i][j] = board[i + x][j - x];
        board[i + x][j - x] = temp;
      } else if (board[i + x][j - x].col != board[i][j].col) {
        square temp = board[i + x][j - x];
        board[i + x][j - x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i + x][j - x].col)) {
          moves.emplace_back(i + x, j - x);
        }

        board[i][j] = board[i + x][j - x];
        board[i + x][j - x] = temp;
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i - x >= 0 and j + x < 8; x++) {
      if (board[i - x][j + x].col == color::null) {
        square temp = board[i - x][j + x];
        board[i - x][j + x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i - x][j + x].col)) {
          moves.emplace_back(i - x, j + x);
        }

        board[i][j] = board[i - x][j + x];
        board[i - x][j + x] = temp;
      } else if (board[i - x][j + x].col != board[i][j].col) {
        square temp = board[i - x][j + x];
        board[i - x][j + x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i - x][j + x].col)) {
          moves.emplace_back(i - x, j + x);
        }

        board[i][j] = board[i - x][j + x];
        board[i - x][j + x] = temp;
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i - x >= 0 and j - x >= 0; x++) {
      if (board[i - x][j - x].col == color::null) {
        square temp = board[i - x][j - x];
        board[i - x][j - x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i - x][j - x].col)) {
          moves.emplace_back(i - x, j - x);
        }

        board[i][j] = board[i - x][j - x];
        board[i - x][j - x] = temp;
      } else if (board[i - x][j - x].col != board[i][j].col) {
        square temp = board[i - x][j - x];
        board[i - x][j - x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i - x][j - x].col)) {
          moves.emplace_back(i - x, j - x);
        }

        board[i][j] = board[i - x][j - x];
        board[i - x][j - x] = temp;
        break;
      } else {
        break;
      }
    }

    break;
  case piece::queen:

    for (int x = i + 1; x < 8; x++) {
      if (board[x][j].col == color::null) {
        square temp = board[x][j];
        board[x][j] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[x][j].col)) {
          moves.emplace_back(x, j);
        }

        board[i][j] = board[x][j];
        board[x][j] = temp;
      } else if (board[x][j].col != board[i][j].col) {
        square temp = board[x][j];
        board[x][j] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[x][j].col)) {
          moves.emplace_back(x, j);
        }

        board[i][j] = board[x][j];
        board[x][j] = temp;
        break;
      } else {
        break;
      }
    }

    for (int x = i - 1; x >= 0; x--) {
      if (board[x][j].col == color::null) {
        square temp = board[x][j];
        board[x][j] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[x][j].col)) {
          moves.emplace_back(x, j);
        }

        board[i][j] = board[x][j];
        board[x][j] = temp;
      } else if (board[x][j].col != board[i][j].col) {
        square temp = board[x][j];
        board[x][j] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[x][j].col)) {
          moves.emplace_back(x, j);
        }

        board[i][j] = board[x][j];
        board[x][j] = temp;
        break;
      } else {
        break;
      }
    }

    for (int y = j + 1; y < 8; y++) {
      if (board[i][y].col == color::null) {
        square temp = board[i][y];
        board[i][y] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i][y].col)) {
          moves.emplace_back(i, y);
        }

        board[i][j] = board[i][y];
        board[i][y] = temp;
      } else if (board[i][y].col != board[i][j].col) {
        square temp = board[i][y];
        board[i][y] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i][y].col)) {
          moves.emplace_back(i, y);
        }

        board[i][j] = board[i][y];
        board[i][y] = temp;
        break;
      } else {
        break;
      }
    }

    for (int y = j - 1; y >= 0; y--) {
      if (board[i][y].col == color::null) {
        square temp = board[i][y];
        board[i][y] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i][y].col)) {
          moves.emplace_back(i, y);
        }

        board[i][j] = board[i][y];
        board[i][y] = temp;
      } else if (board[i][y].col != board[i][j].col) {
        square temp = board[i][y];
        board[i][y] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i][y].col)) {
          moves.emplace_back(i, y);
        }

        board[i][j] = board[i][y];
        board[i][y] = temp;
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i + x < 8 and j + x < 8; x++) {
      if (board[i + x][j + x].col == color::null) {
        square temp = board[i + x][j + x];
        board[i + x][j + x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i + x][j + x].col)) {
          moves.emplace_back(i + x, j + x);
        }

        board[i][j] = board[i + x][j + x];
        board[i + x][j + x] = temp;
      } else if (board[i + x][j + x].col != board[i][j].col) {
        square temp = board[i + x][j + x];
        board[i + x][j + x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i + x][j + x].col)) {
          moves.emplace_back(i + x, j + x);
        }

        board[i][j] = board[i + x][j + x];
        board[i + x][j + x] = temp;
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i + x < 8 and j - x >= 0; x++) {
      if (board[i + x][j - x].col == color::null) {
        square temp = board[i + x][j - x];
        board[i + x][j - x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i + x][j - x].col)) {
          moves.emplace_back(i + x, j - x);
        }

        board[i][j] = board[i + x][j - x];
        board[i + x][j - x] = temp;
      } else if (board[i + x][j - x].col != board[i][j].col) {
        square temp = board[i + x][j - x];
        board[i + x][j - x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i + x][j - x].col)) {
          moves.emplace_back(i + x, j - x);
        }

        board[i][j] = board[i + x][j - x];
        board[i + x][j - x] = temp;
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i - x >= 0 and j + x < 8; x++) {
      if (board[i - x][j + x].col == color::null) {
        square temp = board[i - x][j + x];
        board[i - x][j + x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i - x][j + x].col)) {
          moves.emplace_back(i - x, j + x);
        }

        board[i][j] = board[i - x][j + x];
        board[i - x][j + x] = temp;
      } else if (board[i - x][j + x].col != board[i][j].col) {
        square temp = board[i - x][j + x];
        board[i - x][j + x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i - x][j + x].col)) {
          moves.emplace_back(i - x, j + x);
        }

        board[i][j] = board[i - x][j + x];
        board[i - x][j + x] = temp;
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i - x >= 0 and j - x >= 0; x++) {
      if (board[i - x][j - x].col == color::null) {
        square temp = board[i - x][j - x];
        board[i - x][j - x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i - x][j - x].col)) {
          moves.emplace_back(i - x, j - x);
        }

        board[i][j] = board[i - x][j - x];
        board[i - x][j - x] = temp;
      } else if (board[i - x][j - x].col != board[i][j].col) {
        square temp = board[i - x][j - x];
        board[i - x][j - x] = board[i][j];
        board[i][j] = {piece::null, color::null};

        if (!isInCheck(board[i - x][j - x].col)) {
          moves.emplace_back(i - x, j - x);
        }

        board[i][j] = board[i - x][j - x];
        board[i - x][j - x] = temp;
        break;
      } else {
        break;
      }
    }

    break;
  case piece::knight:

    if (i + 1 < 8 and j + 2 < 8 and
        board[i + 1][j + 2].col != board[i][j].col) {
      square temp = board[i + 1][j + 2];
      board[i + 1][j + 2] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i + 1][j + 2].col)) {
        moves.emplace_back(i + 1, j + 2);
      }

      board[i][j] = board[i + 1][j + 2];
      board[i + 1][j + 2] = temp;
    }

    if (i + 2 < 8 and j + 1 < 8 and
        board[i + 2][j + 1].col != board[i][j].col) {
      square temp = board[i + 2][j + 1];
      board[i + 2][j + 1] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i + 2][j + 1].col)) {
        moves.emplace_back(i + 2, j + 1);
      }

      board[i][j] = board[i + 2][j + 1];
      board[i + 2][j + 1] = temp;
    }

    if (i - 1 >= 0 and j + 2 < 8 and
        board[i - 1][j + 2].col != board[i][j].col) {
      square temp = board[i - 1][j + 2];
      board[i - 1][j + 2] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i - 1][j + 2].col)) {
        moves.emplace_back(i - 1, j + 2);
      }

      board[i][j] = board[i - 1][j + 2];
      board[i - 1][j + 2] = temp;
    }

    if (i - 2 >= 0 and j + 1 < 8 and
        board[i - 2][j + 1].col != board[i][j].col) {
      square temp = board[i - 2][j + 1];
      board[i - 2][j + 1] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i - 2][j + 1].col)) {
        moves.emplace_back(i - 2, j + 1);
      }

      board[i][j] = board[i - 2][j + 1];
      board[i - 2][j + 1] = temp;
    }

    if (i + 1 < 8 and j - 2 >= 0 and
        board[i + 1][j - 2].col != board[i][j].col) {
      square temp = board[i + 1][j - 2];
      board[i + 1][j - 2] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i + 1][j - 2].col)) {
        moves.emplace_back(i + 1, j - 2);
      }

      board[i][j] = board[i + 1][j - 2];
      board[i + 1][j - 2] = temp;
    }

    if (i + 2 < 8 and j - 1 >= 0 and
        board[i + 2][j - 1].col != board[i][j].col) {
      square temp = board[i + 2][j - 1];
      board[i + 2][j - 1] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i + 2][j - 1].col)) {
        moves.emplace_back(i + 2, j - 1);
      }

      board[i][j] = board[i + 2][j - 1];
      board[i + 2][j - 1] = temp;
    }

    if (i - 1 >= 0 and j - 2 >= 0 and
        board[i - 1][j - 2].col != board[i][j].col) {
      square temp = board[i - 1][j - 2];
      board[i - 1][j - 2] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i - 1][j - 2].col)) {
        moves.emplace_back(i - 1, j - 2);
      }

      board[i][j] = board[i - 1][j - 2];
      board[i - 1][j - 2] = temp;
    }

    if (i - 2 >= 0 and j - 1 >= 0 and
        board[i - 2][j - 1].col != board[i][j].col) {
      square temp = board[i - 2][j - 1];
      board[i - 2][j - 1] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i - 2][j - 1].col)) {
        moves.emplace_back(i - 2, j - 1);
      }

      board[i][j] = board[i - 2][j - 1];
      board[i - 2][j - 1] = temp;
    }

    break;
  case piece::king:

    if (i - 1 >= 0 and board[i - 1][j].col != board[i][j].col) {
      square temp = board[i - 1][j];
      board[i - 1][j] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i - 1][j].col)) {
        moves.emplace_back(i - 1, j);
      }

      board[i][j] = board[i - 1][j];
      board[i - 1][j] = temp;
    }

    if (i + 1 < 8 and board[i + 1][j].col != board[i][j].col) {
      square temp = board[i + 1][j];
      board[i + 1][j] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i + 1][j].col)) {
        moves.emplace_back(i + 1, j);
      }

      board[i][j] = board[i + 1][j];
      board[i + 1][j] = temp;
    }

    if (j - 1 >= 0 and board[i][j - 1].col != board[i][j].col) {
      square temp = board[i][j - 1];
      board[i][j - 1] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i][j - 1].col)) {
        moves.emplace_back(i, j - 1);
      }

      board[i][j] = board[i][j - 1];
      board[i][j - 1] = temp;
    }

    if (j + 1 < 8 and board[i][j + 1].col != board[i][j].col) {
      square temp = board[i][j + 1];
      board[i][j + 1] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i][j + 1].col)) {
        moves.emplace_back(i, j + 1);
      }

      board[i][j] = board[i][j + 1];
      board[i][j + 1] = temp;
    }

    if (i - 1 >= 0 and j - 1 >= 0 and
        board[i - 1][j - 1].col != board[i][j].col) {
      square temp = board[i - 1][j - 1];
      board[i - 1][j - 1] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i - 1][j - 1].col)) {
        moves.emplace_back(i - 1, j - 1);
      }

      board[i][j] = board[i - 1][j - 1];
      board[i - 1][j - 1] = temp;
    }

    if (i + 1 < 8 and j - 1 >= 0 and
        board[i + 1][j - 1].col != board[i][j].col) {
      square temp = board[i + 1][j - 1];
      board[i + 1][j - 1] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i + 1][j - 1].col)) {
        moves.emplace_back(i + 1, j - 1);
      }

      board[i][j] = board[i + 1][j - 1];
      board[i + 1][j - 1] = temp;
    }

    if (i - 1 >= 0 and j + 1 < 8 and
        board[i - 1][j + 1].col != board[i][j].col) {
      square temp = board[i - 1][j + 1];
      board[i - 1][j + 1] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i - 1][j + 1].col)) {
        moves.emplace_back(i - 1, j + 1);
      }

      board[i][j] = board[i - 1][j + 1];
      board[i - 1][j + 1] = temp;
    }

    if (i + 1 < 8 and j + 1 < 8 and
        board[i + 1][j + 1].col != board[i][j].col) {
      square temp = board[i + 1][j + 1];
      board[i + 1][j + 1] = board[i][j];
      board[i][j] = {piece::null, color::null};

      if (!isInCheck(board[i + 1][j + 1].col)) {
        moves.emplace_back(i + 1, j + 1);
      }

      board[i][j] = board[i + 1][j + 1];
      board[i + 1][j + 1] = temp;
    }

    if (board[i][j].col == color::light and i == 7 and j == 4 and
        !isInCheck(color::light)) {
      if (canLightCastle1) {
        if (board[7][3].type == piece::null and
            board[7][2].type == piece::null and
            board[7][1].type == piece::null and
            board[7][0].type == piece::rook and
            board[7][0].col == color::light) {
          if (std::find(moves.begin(), moves.end(), std::pair{7, 3}) !=
              moves.end()) {

            square temp = board[7][2];
            board[7][2] = board[i][j];
            board[i][j] = {piece::null, color::null};

            if (!isInCheck(board[7][2].col)) {
              board[i][j] = board[7][2];
              board[7][2] = temp;

              square temp2 = board[7][1];
              board[7][1] = board[i][j];
              board[i][j] = {piece::null, color::null};

              if (!isInCheck(board[7][1].col)) {
                moves.emplace_back(7, 1);
              }

              board[i][j] = board[7][1];
              board[7][2] = temp2;
            } else {
              board[i][j] = board[7][2];
              board[7][2] = temp;
            }
          }
        }
      }

      if (canLightCastle2) {
        if (board[7][5].type == piece::null and
            board[7][6].type == piece::null and
            board[7][7].type == piece::rook and
            board[7][7].col == color::light) {
          if (std::find(moves.begin(), moves.end(), std::pair{7, 5}) !=
              moves.end()) {

            square temp = board[7][6];
            board[7][6] = board[i][j];
            board[i][j] = {piece::null, color::null};

            if (!isInCheck(board[7][6].col)) {
              moves.emplace_back(7, 6);
            }

            board[i][j] = board[7][6];
            board[7][6] = temp;
          }
        }
      }
    } else if (board[i][j].col == color::dark and i == 0 and j == 4 and
               !isInCheck(color::dark)) {
      if (canDarkCastle1) {
        if (board[0][3].type == piece::null and
            board[0][2].type == piece::null and
            board[0][1].type == piece::null and
            board[0][0].type == piece::rook and
            board[0][0].col == color::dark) {
          if (std::find(moves.begin(), moves.end(), std::pair{0, 3}) !=
              moves.end()) {
            square temp = board[0][2];
            board[0][2] = board[i][j];
            board[i][j] = {piece::null, color::null};

            if (!isInCheck(board[0][2].col)) {
              board[i][j] = board[0][2];
              board[0][2] = temp;

              square temp2 = board[0][1];
              board[0][1] = board[i][j];
              board[i][j] = {piece::null, color::null};

              if (!isInCheck(board[0][1].col)) {
                moves.emplace_back(0, 1);
              }

              board[i][j] = board[0][1];
              board[0][1] = temp2;
            } else {
              board[i][j] = board[0][2];
              board[0][2] = temp;
            }
          }
        }
      }

      if (canDarkCastle2) {
        if (board[0][5].type == piece::null and
            board[0][6].type == piece::null and
            board[0][7].type == piece::rook and
            board[0][7].col == color::dark) {
          if (std::find(moves.begin(), moves.end(), std::pair{0, 5}) !=
              moves.end()) {
            square temp = board[0][6];
            board[0][6] = board[i][j];
            board[i][j] = {piece::null, color::null};

            if (!isInCheck(board[0][6].col)) {
              moves.emplace_back(0, 6);
            }

            board[i][j] = board[0][6];
            board[0][6] = temp;
          }
        }
      }
    }

    break;
  default:
    break;
  }
  return moves;
}

std::vector<std::pair<int, int>> chess::getMovesWithoutChecking(
    const std::vector<std::vector<square>> &tempBoard, int i, int j) {
  std::vector<std::pair<int, int>> moves;

  switch (tempBoard[i][j].type) {
  case piece::null:
    break;
  case piece::pawn:
    if (tempBoard[i][j].col == color::light) {
      if (i != 0 and tempBoard[i - 1][j].col == color::null) {
        moves.emplace_back(i - 1, j);

        if (i == 6 and tempBoard[i - 2][j].col == color::null) {
          moves.emplace_back(i - 2, j);
        }
      }

      if (i != 0 and j != 0 and tempBoard[i - 1][j - 1].col == color::dark) {
        moves.emplace_back(i - 1, j - 1);
      }

      if (i != 0 and j != 7 and tempBoard[i - 1][j + 1].col == color::dark) {
        moves.emplace_back(i - 1, j + 1);
      }
    } else {
      if (i != 7 and tempBoard[i + 1][j].col == color::null) {
        moves.emplace_back(i + 1, j);

        if (i == 1 and tempBoard[i + 2][j].col == color::null) {
          moves.emplace_back(i + 2, j);
        }
      }

      if (i != 7 and j != 0 and tempBoard[i + 1][j - 1].col == color::light) {
        moves.emplace_back(i + 1, j - 1);
      }

      if (i != 7 and j != 7 and tempBoard[i + 1][j + 1].col == color::light) {
        moves.emplace_back(i + 1, j + 1);
      }
    }

    break;
  case piece::rook:

    for (int x = i + 1; x < 8; x++) {
      if (tempBoard[x][j].col == color::null) {
        moves.emplace_back(x, j);
      } else if (tempBoard[x][j].col != tempBoard[i][j].col) {
        moves.emplace_back(x, j);
        break;
      } else {
        break;
      }
    }

    for (int x = i - 1; x >= 0; x--) {
      if (tempBoard[x][j].col == color::null) {
        moves.emplace_back(x, j);
      } else if (tempBoard[x][j].col != tempBoard[i][j].col) {
        moves.emplace_back(x, j);
        break;
      } else {
        break;
      }
    }

    for (int y = j + 1; y < 8; y++) {
      if (tempBoard[i][y].col == color::null) {
        moves.emplace_back(i, y);
      } else if (tempBoard[i][y].col != tempBoard[i][j].col) {
        moves.emplace_back(i, y);
        break;
      } else {
        break;
      }
    }

    for (int y = j - 1; y >= 0; y--) {
      if (tempBoard[i][y].col == color::null) {
        moves.emplace_back(i, y);
      } else if (tempBoard[i][y].col != tempBoard[i][j].col) {
        moves.emplace_back(i, y);
        break;
      } else {
        break;
      }
    }

    break;
  case piece::bishop:

    for (int x = 1; i + x < 8 and j + x < 8; x++) {
      if (tempBoard[i + x][j + x].col == color::null) {
        moves.emplace_back(i + x, j + x);
      } else if (tempBoard[i + x][j + x].col != tempBoard[i][j].col) {
        moves.emplace_back(i + x, j + x);
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i + x < 8 and j - x >= 0; x++) {
      if (tempBoard[i + x][j - x].col == color::null) {
        moves.emplace_back(i + x, j - x);
      } else if (tempBoard[i + x][j - x].col != tempBoard[i][j].col) {
        moves.emplace_back(i + x, j - x);
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i - x >= 0 and j + x < 8; x++) {
      if (tempBoard[i - x][j + x].col == color::null) {
        moves.emplace_back(i - x, j + x);
      } else if (tempBoard[i - x][j + x].col != tempBoard[i][j].col) {
        moves.emplace_back(i - x, j + x);
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i - x >= 0 and j - x >= 0; x++) {
      if (tempBoard[i - x][j - x].col == color::null) {
        moves.emplace_back(i - x, j - x);
      } else if (tempBoard[i - x][j - x].col != tempBoard[i][j].col) {
        moves.emplace_back(i - x, j - x);
        break;
      } else {
        break;
      }
    }

    break;
  case piece::queen:

    for (int x = i + 1; x < 8; x++) {
      if (tempBoard[x][j].col == color::null) {
        moves.emplace_back(x, j);
      } else if (tempBoard[x][j].col != tempBoard[i][j].col) {
        moves.emplace_back(x, j);
        break;
      } else {
        break;
      }
    }

    for (int x = i - 1; x >= 0; x--) {
      if (tempBoard[x][j].col == color::null) {
        moves.emplace_back(x, j);
      } else if (tempBoard[x][j].col != tempBoard[i][j].col) {
        moves.emplace_back(x, j);
        break;
      } else {
        break;
      }
    }

    for (int y = j + 1; y < 8; y++) {
      if (tempBoard[i][y].col == color::null) {
        moves.emplace_back(i, y);
      } else if (tempBoard[i][y].col != tempBoard[i][j].col) {
        moves.emplace_back(i, y);
        break;
      } else {
        break;
      }
    }

    for (int y = j - 1; y >= 0; y--) {
      if (tempBoard[i][y].col == color::null) {
        moves.emplace_back(i, y);
      } else if (tempBoard[i][y].col != tempBoard[i][j].col) {
        moves.emplace_back(i, y);
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i + x < 8 and j + x < 8; x++) {
      if (tempBoard[i + x][j + x].col == color::null) {
        moves.emplace_back(i + x, j + x);
      } else if (tempBoard[i + x][j + x].col != tempBoard[i][j].col) {
        moves.emplace_back(i + x, j + x);
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i + x < 8 and j - x >= 0; x++) {
      if (tempBoard[i + x][j - x].col == color::null) {
        moves.emplace_back(i + x, j - x);
      } else if (tempBoard[i + x][j - x].col != tempBoard[i][j].col) {
        moves.emplace_back(i + x, j - x);
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i - x >= 0 and j + x < 8; x++) {
      if (tempBoard[i - x][j + x].col == color::null) {
        moves.emplace_back(i - x, j + x);
      } else if (tempBoard[i - x][j + x].col != tempBoard[i][j].col) {
        moves.emplace_back(i - x, j + x);
        break;
      } else {
        break;
      }
    }

    for (int x = 1; i - x >= 0 and j - x >= 0; x++) {
      if (tempBoard[i - x][j - x].col == color::null) {
        moves.emplace_back(i - x, j - x);
      } else if (tempBoard[i - x][j - x].col != tempBoard[i][j].col) {
        moves.emplace_back(i - x, j - x);
        break;
      } else {
        break;
      }
    }

    break;
  case piece::knight:

    if (i + 1 < 8 and j + 2 < 8 and
        tempBoard[i + 1][j + 2].col != tempBoard[i][j].col) {
      moves.emplace_back(i + 1, j + 2);
    }

    if (i + 2 < 8 and j + 1 < 8 and
        tempBoard[i + 2][j + 1].col != tempBoard[i][j].col) {
      moves.emplace_back(i + 2, j + 1);
    }

    if (i - 1 >= 0 and j + 2 < 8 and
        tempBoard[i - 1][j + 2].col != tempBoard[i][j].col) {
      moves.emplace_back(i - 1, j + 2);
    }

    if (i - 2 >= 0 and j + 1 < 8 and
        tempBoard[i - 2][j + 1].col != tempBoard[i][j].col) {
      moves.emplace_back(i - 2, j + 1);
    }

    if (i + 1 < 8 and j - 2 >= 0 and
        tempBoard[i + 1][j - 2].col != tempBoard[i][j].col) {
      moves.emplace_back(i + 1, j - 2);
    }

    if (i + 2 < 8 and j - 1 >= 0 and
        tempBoard[i + 2][j - 1].col != tempBoard[i][j].col) {
      moves.emplace_back(i + 2, j - 1);
    }

    if (i - 1 >= 0 and j - 2 >= 0 and
        tempBoard[i - 1][j - 2].col != tempBoard[i][j].col) {
      moves.emplace_back(i - 1, j - 2);
    }

    if (i - 2 >= 0 and j - 1 >= 0 and
        tempBoard[i - 2][j - 1].col != tempBoard[i][j].col) {
      moves.emplace_back(i - 2, j - 1);
    }

    break;
  case piece::king:

    if (i - 1 >= 0 and tempBoard[i - 1][j].col != tempBoard[i][j].col) {
      moves.emplace_back(i - 1, j);
    }

    if (i + 1 < 8 and tempBoard[i + 1][j].col != tempBoard[i][j].col) {
      moves.emplace_back(i + 1, j);
    }

    if (j - 1 >= 0 and tempBoard[i][j - 1].col != tempBoard[i][j].col) {
      moves.emplace_back(i, j - 1);
    }

    if (j + 1 < 8 and tempBoard[i][j + 1].col != tempBoard[i][j].col) {
      moves.emplace_back(i, j + 1);
    }

    if (i - 1 >= 0 and j - 1 >= 0 and
        tempBoard[i - 1][j - 1].col != tempBoard[i][j].col) {
      moves.emplace_back(i - 1, j - 1);
    }

    if (i + 1 < 8 and j - 1 >= 0 and
        tempBoard[i + 1][j - 1].col != tempBoard[i][j].col) {
      moves.emplace_back(i + 1, j - 1);
    }

    if (i - 1 >= 0 and j + 1 < 8 and
        tempBoard[i - 1][j + 1].col != tempBoard[i][j].col) {
      moves.emplace_back(i - 1, j + 1);
    }

    if (i + 1 < 8 and j + 1 < 8 and
        tempBoard[i + 1][j + 1].col != tempBoard[i][j].col) {
      moves.emplace_back(i + 1, j + 1);
    }

    if (tempBoard[i][j].col == color::light and i == 7 and j == 4) {
      if (canLightCastle1) {
        if (tempBoard[7][3].type == piece::null and
            tempBoard[7][2].type == piece::null and
            tempBoard[7][1].type == piece::null and
            tempBoard[7][0].type == piece::rook and
            tempBoard[7][0].col == color::light) {
          moves.emplace_back(7, 1);
        }
      }

      if (canLightCastle2) {
        if (tempBoard[7][5].type == piece::null and
            tempBoard[7][6].type == piece::null and
            tempBoard[7][7].type == piece::rook and
            tempBoard[7][7].col == color::light) {
          moves.emplace_back(7, 6);
        }
      }
    } else if (tempBoard[i][j].col == color::dark and i == 0 and j == 4) {
      if (canDarkCastle1) {
        if (tempBoard[0][3].type == piece::null and
            tempBoard[0][2].type == piece::null and
            tempBoard[0][1].type == piece::null and
            tempBoard[0][0].type == piece::rook and
            tempBoard[0][0].col == color::dark) {
          moves.emplace_back(0, 1);
        }
      }

      if (canDarkCastle2) {
        if (tempBoard[0][5].type == piece::null and
            tempBoard[0][6].type == piece::null and
            tempBoard[0][7].type == piece::rook and
            tempBoard[0][7].col == color::dark) {
          moves.emplace_back(0, 6);
        }
      }
    }

    break;
  default:
    break;
  }

  return moves;
}

bool chess::isInCheck(const color &col) {
  int x = -1, y = -1;

  for (size_t i = 0; i < board.size(); i++) {
    for (size_t j = 0; j < board[i].size(); j++) {
      if (board[i][j].col == col and board[i][j].type == piece::king) {
        x = i, y = j;
        break;
      }
    }
  }

  for (size_t i = 0; i < board.size(); i++) {
    for (size_t j = 0; j < board[i].size(); j++) {
      if (board[i][j].col != col and board[i][j].col != color::null) {
        std::vector<std::pair<int, int>> moves =
            getMovesWithoutChecking(board, i, j);

        for (const auto &[I, J] : moves) {
          if (I == x and J == y) {
            return true;
          }
        }
      }
    }
  }

  return false;
}

bool chess::isCheckMate(const color &col) {
  if (!isInCheck(col)) {
    return false;
  }

  for (size_t i = 0; i < board.size(); i++) {
    for (size_t j = 0; j < board[i].size(); j++) {
      if (board[i][j].col == col) {
        std::vector<std::pair<int, int>> moves = getMoves(i, j);

        if (!moves.empty()) {
          return false;
        }
      }
    }
  }

  return true;
}

bool chess::isStaleMate(const color &col) {
  if (isInCheck(col)) {
    return false;
  }

  for (size_t i = 0; i < board.size(); i++) {
    for (size_t j = 0; j < board.size(); j++) {
      if (board[i][j].col == col) {
        std::vector<std::pair<int, int>> moves = getMoves(i, j);

        if (!moves.empty()) {
          return false;
        }
      }
    }
  }

  return true;
}

std::optional<char> chess::pieceToChar(const piece &p) {
  switch (p) {
  case piece::null:
  case piece::pawn:
    return {};
    break;
  case piece::king:
    return 'K';
    break;
  case piece::rook:
    return 'R';
    break;
  case piece::queen:
    return 'Q';
    break;
  case piece::bishop:
    return 'B';
    break;
  case piece::knight:
    return 'N';
    break;
  }
  return {};
}

std::string chess::move(int i, int j, int I, int J) {
  std::string notation;
  std::optional<char> c = pieceToChar(board[i][j].type);

  if (board[I][J].type == piece::null) {
    if (c) {
      notation += c.value();
    }

    notation += char('a' + J);
    notation += '0' + (8 - I);
  } else {
    if (c) {
      notation += c.value();
    } else if (board[i][j].type == piece::pawn) {
      notation += char('a' + j);
    }

    notation += 'x';
    notation += char('a' + J);
    notation += '0' + (8 - I);
  }

  board[I][J] = board[i][j];
  board[i][j] = {piece::null, color::null};

  if (isCheckMate(board[I][J].col == color::light ? color::dark
                                                  : color::light)) {
    notation += '#';
  } else if (isInCheck(board[I][J].col == color::light ? color::dark
                                                       : color::light)) {
    notation += '+';
  }

  return notation;
}
