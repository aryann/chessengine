#include "perft.h"

#include <map>
#include <vector>

#include "move.h"
#include "move_generator.h"
#include "position.h"
#include "scoped_move.h"

namespace chessengine {

namespace {

void RunPerft(std::size_t depth, std::size_t current_depth, Position &position,
              std::optional<Move> start_move,
              std::vector<std::size_t> &depth_counts,
              std::map<Move, std::size_t> &final_move_counts) {
  ++depth_counts[current_depth];

  if (depth == current_depth) {
    ++final_move_counts[*start_move];
    return;
  }

  std::vector<Move> moves = GenerateMoves(position);

  for (const Move &move : moves) {
    ScopedMove scoped_move(move, position);

    if (position.GetCheckers(~position.SideToMove())) {
      continue;
    }

    RunPerft(depth, current_depth + 1, position, start_move ? start_move : move,
             depth_counts, final_move_counts);
  }
}

}  // namespace

void RunPerft(std::size_t depth, Position &position,
              std::vector<std::size_t> &depth_counts,
              std::map<Move, std::size_t> &final_move_counts) {
  depth_counts.resize(depth + 1, 0);

  RunPerft(depth, 0, position, std::nullopt, depth_counts, final_move_counts);
}

}  // namespace chessengine
