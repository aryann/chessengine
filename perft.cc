#include "perft.h"

#include <map>
#include <vector>

#include "move.h"
#include "move_generator.h"
#include "position.h"
#include "scoped_move.h"

namespace chessengine {

namespace {

void RunPerft(std::size_t depth,
              Position &position,
              std::optional<Move> current_move,
              std::vector<std::size_t> &depth_counts,
              std::map<Move, std::size_t> &final_move_counts) {
    // TODO(aryann): Find a better way to determine that the game is over.
    bool has_both_kings = position.GetPieces(kKing).GetCount() == 2;
    if (!has_both_kings) {
        return;
    }

    ++depth_counts[depth_counts.size() - depth - 1];

    if (depth == 0) {
        ++final_move_counts[*current_move];
        return;
    }

    Side side = position.SideToMove();

    std::vector<Move> moves;
    if (position.GetCheckers(side)) {
        moves = GenerateMoves<kEvasion>(position);
    } else {
        moves = GenerateMoves<kQuiet, kCapture>(position);
    }

    for (const Move &move: moves) {
        ScopedMove scoped_move(move, position);

        if (!position.GetCheckers(side)) {
            RunPerft(depth - 1, position, move, depth_counts, final_move_counts);
        }
    }
}

} // namespace

void RunPerft(std::size_t depth,
              Position &position,
              std::vector<std::size_t> &depth_counts,
              std::map<Move, std::size_t> &final_move_counts) {
    depth_counts.resize(depth + 1, 0);
    RunPerft(depth, position, std::nullopt, depth_counts, final_move_counts);
}

} // namespace chessengine
