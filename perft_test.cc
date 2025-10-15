#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "move.h"
#include "move_generator.h"
#include "position.h"

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::ElementsAre;

void RunPerft(int depth, Position &position, std::vector<int> &nodes, std::map<Move, int> &unique_counts) {
    ++nodes[nodes.size() - depth];

    if (depth <= 1) {
        return;
    }

    std::vector<Move> moves = GenerateMoves<kQuiet>(position);
    for (const Move &move: moves) {
        if (depth == 2) {
            ++unique_counts[move];
        }

        position.Do(move);
        RunPerft(depth - 1, position, nodes, unique_counts);
        position.Undo(move);
    }
}

TEST(Perft, StartingPosition) {
    const int depth = 3;

    std::map<Move, int> unique_counts;

    Position position = Position::Starting();
    std::vector<int> nodes(depth);
    RunPerft(depth, position, nodes, unique_counts);

    for (auto [move, count]: unique_counts) {
        std::cout << move << ": " << count << std::endl;
    }

    EXPECT_THAT(nodes, ElementsAre(1, 20, 400));
}

} // namespace
} // namespace chessengine
