#include <list>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class chess {
public:
  enum class piece {
    pawn,
    bishop,
    knight,
    rook,
    queen,
    king,
    null,
  };

  enum class color {
    dark,
    light,
    null,
  };

  struct square {
    piece type;
    color col;
  };

  std::vector<std::vector<square>> board;
  std::list<std::string> moves;
  std::pair<int, int> selected;
  std::pair<int, int> switcher;
  bool isSelected;
  bool switching;
  bool canLightCastle1, canLightCastle2;
  bool canDarkCastle1, canDarkCastle2;
  color turn;

  chess();
  bool isInCheck(const color &col);
  bool isCheckMate(const color &col);
  bool isStaleMate(const color &col);
  std::string move(int i, int j, int I, int J);
  std::vector<std::pair<int, int>> getMoves(int i, int j);

private:
  std::vector<std::pair<int, int>>
  getMovesWithoutChecking(const std::vector<std::vector<square>> &tempBoard,
                          int i, int j);
  std::optional<char> pieceToChar(const piece &p);
};
