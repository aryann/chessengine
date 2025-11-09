#ifndef CHESS_ENGINE_ZOBRIST_H_
#define CHESS_ENGINE_ZOBRIST_H_

#include <random>

#include "engine/types.h"

namespace chessengine {

struct ZobristKeys {
  ZobristKeys();

  std::array<std::array<std::array<std::uint64_t, kNumSides>, kNumPieces>,
             kNumSquares>
      elements;
  std::array<std::uint64_t, kFiles> en_passant_files;

  std::uint64_t black_to_move;
};

inline ZobristKeys::ZobristKeys() : elements(), en_passant_files() {
  std::mt19937 engine(std::random_device{}());
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

// N.B.: ZobristKeys relies on a random number generator, so it cannot be
// defined as a constexpr variable.
inline const ZobristKeys kZobristKeys;

class ZobristKey {
 public:
  ZobristKey() : key_(0ULL) {}

  constexpr void Update(Square square, Piece piece, Side side) {
    key_ ^= kZobristKeys.elements[square][piece][side];
  }

  constexpr void UpdateSideToMove() { key_ ^= kZobristKeys.black_to_move; }

  constexpr void ToggleEnPassantTarget(Square target) {
    key_ ^= kZobristKeys.en_passant_files[GetFile(target)];
  }

  [[nodiscard]] std::uint64_t GetKey() const { return key_; }

  constexpr auto operator<=>(const ZobristKey& other) const = default;

 private:
  std::uint64_t key_;
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_ZOBRIST_H_
