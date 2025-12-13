#include "search/move_ordering.h"

#include <functional>
#include <vector>

#include "engine/move.h"
#include "engine/position.h"

namespace follychess {
namespace {

[[nodiscard]] int MoveKey(const Position& position, Move move) {
  if (move.IsCapture()) {
    const Piece attacker = position.GetPiece(move.GetFrom());
    const Piece victim = position.GetPiece(move.GetTo());

    const int victim_score = kKing - victim;
    const int attacker_score = attacker;

    return (victim_score * static_cast<int>(kNumPieces)) + attacker_score;
  }

  return 1'000;
}

}  // namespace

void OrderMoves(const Position& position, std::vector<Move>& moves) {
  std::ranges::sort(moves, std::less(), std::bind_front(MoveKey, position));
}

}  // namespace follychess
