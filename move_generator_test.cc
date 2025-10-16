#include "move_generator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "position.h"
#include "testing.h"

namespace chessengine {
namespace {
using ::testing::Eq;
using ::testing::UnorderedElementsAre;

TEST(GenerateMoves, QuietMoves_StartingPosition) {
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

TEST(GenerateMoves, QuietMoves_StartingPosition2) {
    Position position = MakePosition(
            "8: r n b q k b n r"
            "7: p p . p p p p p"
            "6: . . . . . . . ."
            "5: . . p . . . . ."
            "4: . . . . P . . ."
            "3: . . . . . . . ."
            "2: P P P P . P P P"
            "1: R N B Q K B N R"
            "   a b c d e f g h"
            //
            "   w KQkq c6 0 2"
            );

    EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAre(
                    // Pawn single moves:
                    Move(A2, A3),
                    Move(B2, B3),
                    Move(C2, C3),
                    Move(D2, D3),
                    Move(E4, E5),
                    Move(F2, F3),
                    Move(G2, G3),
                    Move(H2, H3),

                    // Pawn double moves:
                    Move(A2, A4),
                    Move(B2, B4),
                    Move(C2, C4),
                    Move(D2, D4),
                    Move(F2, F4),
                    Move(G2, G4),
                    Move(H2, H4),

                    // Knight moves:
                    Move(B1, A3),
                    Move(B1, C3),
                    Move(G1, F3),
                    Move(G1, H3),
                    Move(G1, E2),

                    // Bishop moves:
                    Move(F1, A6),
                    Move(F1, B5),
                    Move(F1, C4),
                    Move(F1, D3),
                    Move(F1, E2),

                    // Queen moves:
                    Move(D1, E2),
                    Move(D1, F3),
                    Move(D1, G4),
                    Move(D1, H5),

                    // King move:
                    Move(E1, E2)
                ));
}

TEST(Pawns, QuietPromotions) {
    Position position = MakePosition(
            "8: . . . . . . . ."
            "7: . . . . P . . ."
            "6: . . . . . . . ."
            "5: . . . . . . . ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: . . . . . . . ."
            "   a b c d e f g h"
            //
            "   w KQkq - 0 1"
            );

    EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAre(
                    Move(E7, E8, MoveOptions().SetPromoted(kQueen)),
                    Move(E7, E8, MoveOptions().SetPromoted(kRook)),
                    Move(E7, E8, MoveOptions().SetPromoted(kKnight)),
                    Move(E7, E8, MoveOptions().SetPromoted(kBishop))
                ));
}

} // namespace
} // namespace chessengine
