#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "move.h"
#include "move_generator.h"
#include "position.h"

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::ElementsAre;

void RunPerft(int depth, Position &position, std::vector<int> &nodes) {
    ++nodes[nodes.size() - depth];

    if (depth <= 1) {
        return;
    }

    std::vector<Move> moves = GenerateMoves<kQuiet>(position);
    for (const Move &move: moves) {
        position.Do(move);
        RunPerft(depth - 1, position, nodes);
        position.Undo(move);
    }
}

TEST(Perft, StartingPosition) {
    const int depth = 3;

    Position position = Position::Starting();
    std::vector<int> nodes(depth);
    RunPerft(depth, position, nodes);

    EXPECT_THAT(nodes, ElementsAre(1, 20, 400));
}

} // namespace
} // namespace chessengine
