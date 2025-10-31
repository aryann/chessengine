#include "perft.h"

#include <map>
#include <vector>

#include "absl/log/log.h"
#include "move.h"
#include "move_generator.h"
#include "position.h"
#include "scoped_move.h"

namespace chessengine {
namespace {

std::size_t RunPerft(std::size_t depth, std::size_t current_depth,
                     Position &position, Move start_move,
                     std::vector<std::size_t> &depth_counts) {
  ++depth_counts[current_depth];

  if (depth == current_depth) {
    return 1;
  }

  std::vector<Move> moves = GenerateMoves(position);
  std::size_t final_move_count = 0;

  for (const Move &move : moves) {
    ScopedMove scoped_move(move, position);

    if (position.GetCheckers(~position.SideToMove())) {
      continue;
    }
    final_move_count +=
        RunPerft(depth, current_depth + 1, position, start_move, depth_counts);
  }

  return final_move_count;
}

}  // namespace

void RunPerft(std::size_t depth, Position &position,
              std::vector<std::size_t> &depth_counts,
              std::map<Move, std::size_t> &final_move_counts) {
  depth_counts.resize(depth + 1, 0);
  depth_counts[0] = 1;
  if (depth == 0) {
    return;
  }

  std::vector<Move> initial_moves = GenerateMoves(position);

  for (const Move move : initial_moves) {
    Position new_position = position;
    new_position.Do(move);
    if (new_position.GetCheckers(~new_position.SideToMove())) {
      continue;
    }
    final_move_counts[move] =
        RunPerft(depth, 1, new_position, move, depth_counts);
  }
}

}  // namespace chessengine
