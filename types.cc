#include "types.h"

#include <format>
#include <string>

namespace chessengine {

std::optional<Square> ParseSquare(std::string_view input) {
  if (input.size() != 2) {
    return std::nullopt;
  }

  char file = input[0];
  char rank = input[1];

  if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
    return std::nullopt;
  }

  int file_index = file - 'a';
  int rank_index = rank - '0';
  int square = (8 - rank_index) * 8 + file_index;
  return static_cast<Square>(square);
}

std::string ToString(Square square) {
  int rank = 8 - square / 8;
  char file = 'a' + square % 8;
  return file + std::to_string(rank);
}

}  // namespace chessengine
