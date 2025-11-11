#include "search/random_search.h"

#include <vector>

#include "engine/move.h"
#include "engine/move_generator.h"
#include "engine/position.h"
#include "engine/scoped_move.h"
#include "engine/types.h"

namespace chessengine {
namespace {

template <typename T>
const T& GetRandomElement(const std::vector<T>& items) {
  static std::mt19937 kEngine(std::random_device{}());
  std::uniform_int_distribution<std::uint64_t> dist(0, items.size() - 1);
  std::size_t random_index = dist(kEngine);
  return items[random_index];
}

}  // namespace

Move RandomSearch(const Position& position, int depth) {
  Position mutable_position = position;
  std::vector<Move> pseudo_legal_moves = GenerateMoves(position);

  std::vector<Move> legal_moves;
  for (const Move& move : pseudo_legal_moves) {
    ScopedMove scoped_move(move, mutable_position);
    if (mutable_position.GetCheckers(~mutable_position.SideToMove())) {
      continue;
    }
    legal_moves.push_back(move);
  }

  return GetRandomElement(legal_moves);
}

}  // namespace chessengine
