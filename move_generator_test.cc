#include "move_generator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "position.h"
#include "testing.h"

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::UnorderedElementsAre;

TEST(GenerateMoves, QuietKnightMoves) {
    auto position = Position::Make();

    EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAre(
                    Move(B1, A3),
                    Move(B1, C3),
                    Move(G1, F3),
                    Move(G1, H3)
                ));
}

} // namespace
} // namespace chessengine

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
