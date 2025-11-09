#include "engine/zobrist.h"

#include <random>

namespace chessengine {
namespace {

struct ZobristKeys {
  ZobristKeys();

  std::array<std::array<std::array<std::uint64_t, kNumSides>, kNumPieces>,
             kNumSquares>
      elements;
  std::array<std::uint64_t, kFiles> en_passant_files;

  std::uint64_t black_to_move;
};

ZobristKeys::ZobristKeys() {
  static std::mt19937 engine(std::random_device{}());
  std::uniform_int_distribution<std::uint64_t> dist(0);

  for (int i = 0; i < kNumSquares; ++i) {
    DCHECK_EQ(elements.size(), kNumSquares);

    for (int j = 0; j < kNumPieces; ++j) {
      DCHECK_EQ(elements[i].size(), kNumPieces);

      for (int k = 0; k < kNumSides; ++k) {
        DCHECK_EQ(elements[i][j].size(), kNumSides);
        elements[i][j][k] = dist(engine);
      }
    }
  }

  for (std::uint64_t& file : en_passant_files) {
    file = dist(engine);
  }

  black_to_move = dist(engine);
}

ZobristKeys kZobristKeys;

}  // namespace

void ZobristHash::Update(Square square, Piece piece, Side side) {
  hash_ ^= kZobristKeys.elements[square][piece][side];
}

void ZobristHash::UpdateSideToMove() { hash_ ^= kZobristKeys.black_to_move; }

void ZobristHash::ToggleEnPassantTarget(Square target) {
  hash_ ^= kZobristKeys.en_passant_files[GetFile(target)];
}

}  // namespace chessengine
