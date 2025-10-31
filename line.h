#ifndef CHESS_ENGINE_LINE_H_
#define CHESS_ENGINE_LINE_H_

#include "bitboard.h"
#include "types.h"

namespace chessengine {

template <Direction Direction>
consteval void FillFromOrigin(Square from,
                              std::array<Bitboard, kNumSquares> &lines) {
  Bitboard result(from);
  Bitboard curr(from);

  while (curr) {
    curr = curr.Shift<Direction>();
    if (!curr) {
      break;
    }

    Square to = curr.LeastSignificantBit();
    lines[to] = result;
    result |= curr;
  }
}

consteval auto GenerateLineTable() {
  std::array<std::array<Bitboard, kNumSquares>, kNumSquares> lines;

  for (int square = A8; square < kNumSquares; ++square) {
    Square from = static_cast<Square>(square);
    std::array<Bitboard, kNumSquares> &curr = lines[square];

    FillFromOrigin<kNorth>(from, curr);
    FillFromOrigin<kNorthEast>(from, curr);
    FillFromOrigin<kEast>(from, curr);
    FillFromOrigin<kSouthEast>(from, curr);
    FillFromOrigin<kSouth>(from, curr);
    FillFromOrigin<kSouthWest>(from, curr);
    FillFromOrigin<kWest>(from, curr);
    FillFromOrigin<kNorthWest>(from, curr);
  }

  return lines;
}

// Gets a bitboard of squares on the line from `from` to `to`. The range is
// inclusive of `from` and exclusive of `to`, i.e., [`from`, `to`).
constexpr Bitboard GetLine(Square from, Square to) {
  static constexpr std::array<std::array<Bitboard, kNumSquares>, kNumSquares>
      kLineTable = GenerateLineTable();
  return kLineTable[from][to];
}

}  // namespace chessengine

#endif  // CHESS_ENGINE_LINE_H_
