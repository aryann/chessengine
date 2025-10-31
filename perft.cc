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
              std::vector<std::size_t> &final_depth_counts,
              std::map<Move, std::size_t> &final_move_counts) {
  if (depth == 0) {
    return;
  }

  std::vector<Move> initial_moves = GenerateMoves(position);
  std::vector<std::vector<std::size_t>> all_depth_counts(
      initial_moves.size(), std::vector<std::size_t>(depth + 1, 0));

  for (int i = 0; i < initial_moves.size(); ++i) {
    Move move = initial_moves[i];
    Position new_position = position;
    new_position.Do(move);
    if (new_position.GetCheckers(~new_position.SideToMove())) {
      continue;
    }

    std::vector<std::size_t> depth_counts(depth + 1, 0);
    final_move_counts[move] =
        RunPerft(depth, 1, new_position, move, all_depth_counts[i]);
  }

  final_depth_counts.resize(depth + 1, 0);
  final_depth_counts[0] = 1;
  for (const std::vector<std::size_t> &depth_counts : all_depth_counts) {
    for (int i = 0; i < depth_counts.size(); ++i) {
      final_depth_counts[i] += depth_counts[i];
    }
  }
}

}  // namespace chessengine
