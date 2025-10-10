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
    auto position = Position::Starting();

    EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAre(
                    // Pawn single moves:
                    Move(A2, A3),
                    Move(B2, B3),
                    Move(C2, C3),
                    Move(D2, D3),
                    Move(E2, E3),
                    Move(F2, F3),
                    Move(G2, G3),
                    Move(H2, H3),

                    // Pawn double moves:
                    Move(A2, A4),
                    Move(B2, B4),
                    Move(C2, C4),
                    Move(D2, D4),
                    Move(E2, E4),
                    Move(F2, F4),
                    Move(G2, G4),
                    Move(H2, H4),

                    // Knight moves:
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
