#ifndef CHESS_ENGINE_ZOBRIST_H_
#define CHESS_ENGINE_ZOBRIST_H_

#include "engine/types.h"

namespace chessengine {

class ZobristKey {
 public:
  ZobristKey() : key_(0ULL) {}

  void Update(Square square, Piece piece, Side side);

  void UpdateSideToMove();

  void ToggleEnPassantTarget(Square target);

  [[nodiscard]] std::uint64_t GetKey() const { return key_; }

  constexpr auto operator<=>(const ZobristKey &other) const = default;

 private:
  std::uint64_t key_;
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_ZOBRIST_H_
