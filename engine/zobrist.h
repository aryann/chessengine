#ifndef CHESS_ENGINE_ZOBRIST_H_
#define CHESS_ENGINE_ZOBRIST_H_

#include "engine/types.h"

namespace chessengine {

class ZobristHash {
 public:
  ZobristHash() : hash_(0ULL) {}

  void Update(Square square, Piece piece, Side side);

  void UpdateSideToMove();

  void ToggleEnPassantTarget(Square target);

  [[nodiscard]] std::uint64_t GetHash() const { return hash_; }

  constexpr auto operator<=>(const ZobristHash &other) const = default;

 private:
  std::uint64_t hash_;
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_ZOBRIST_H_
