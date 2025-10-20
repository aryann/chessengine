#include "move_generator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "position.h"
#include "testing.h"

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::IsEmpty;
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
    //
    {
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
                        Move(E7, E8, kQueen),
                        Move(E7, E8, kRook),
                        Move(E7, E8, kKnight),
                        Move(E7, E8, kBishop)
                    ));
    }
    //
    {
        Position position = MakePosition(
                "8: . . . . . . . ."
                "7: . . . . . . . ."
                "6: . . . . . . . ."
                "5: . . . . . . . ."
                "4: . . . . . . . ."
                "3: . . . . . . . ."
                "2: p . . . . . . ."
                "1: . . . . . . . ."
                "   a b c d e f g h"
                //
                "   b KQkq - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAre(
                        Move(A2, A1, kQueen),
                        Move(A2, A1, kRook),
                        Move(A2, A1, kKnight),
                        Move(A2, A1, kBishop)
                    ));
    }
}

TEST(Pawns, Captures) {
    //
    {
        Position position = MakePosition(
                "8: . . . . . . . ."
                "7: . . . . . . . ."
                "6: . . . . . . . ."
                "5: . . . . . . . ."
                "4: . . . p . r . ."
                "3: . . . . P . . ."
                "2: . . . . . . . ."
                "1: . . . . . . . ."
                "   a b c d e f g h"
                //
                "   w KQkq - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kCapture>(position), UnorderedElementsAre(
                        Move(E3, D4),
                        Move(E3, F4)
                    ));
    }
    //
    {
        Position position = MakePosition(
                "8: . . . . . . . ."
                "7: . . . . . . . ."
                "6: . . . . . . . ."
                "5: . . . p . . . ."
                "4: . . P . R . . ."
                "3: . . . . . . . ."
                "2: . . . . . . . ."
                "1: . . . . . . . ."
                "   a b c d e f g h"
                //
                "   b KQkq - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kCapture>(position), UnorderedElementsAre(
                        Move(D5, C4),
                        Move(D5, E4)
                    ));
    }
}

TEST(Knights, QuietMoves) {
    //
    {
        Position position = MakePosition(
                "8: . . . . . . . ."
                "7: . . . . . . . ."
                "6: . . . . . . . ."
                "5: . . . . . . . ."
                "4: . . . . . . . ."
                "3: . . . . N . . ."
                "2: . . . . . . . ."
                "1: . . . . . . . ."
                "   a b c d e f g h"
                //
                "   w KQkq - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAre(
                        Move(E3, D5),
                        Move(E3, F5),
                        Move(E3, C4),
                        Move(E3, G4),
                        Move(E3, C2),
                        Move(E3, G2),
                        Move(E3, D1),
                        Move(E3, F1)
                    ));
    }
    //
    {
        Position position = MakePosition(
                "8: . . . . . . . ."
                "7: . . . . . . . ."
                "6: . . . . . . . ."
                "5: . . . r . r . ."
                "4: . . . . . . . ."
                "3: . . . . N . . ."
                "2: . . . . . . . ."
                "1: . . . r . r . ."
                "   a b c d e f g h"
                //
                "   w KQkq - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAre(
                        Move(E3, C2),
                        Move(E3, C4),
                        Move(E3, G2),
                        Move(E3, G4)
                    ));
    }
}

TEST(Knights, Captures) {
    //
    {
        Position position = MakePosition(
                "8: . . . . . . . ."
                "7: . . . . . . . ."
                "6: . . . . . . . ."
                "5: . . . . . . . ."
                "4: . . . . . . . ."
                "3: . . . . N . . ."
                "2: . . . . . . . ."
                "1: . . . . . . . ."
                "   a b c d e f g h"
                //
                "   w KQkq - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kCapture>(position), IsEmpty());
    }
    //
    {
        Position position = MakePosition(
                "8: . . . . . . . ."
                "7: . . . . . . . ."
                "6: . . . . . . . ."
                "5: . . . b . b . ."
                "4: . . . . . . . ."
                "3: . . . . N . . ."
                "2: . . . . . . . ."
                "1: . . . r . r . ."
                "   a b c d e f g h"
                //
                "   w KQkq - 12 20"
                );

        EXPECT_THAT(GenerateMoves<kCapture>(position), UnorderedElementsAre(
                        Move(E3, D1),
                        Move(E3, D5),
                        Move(E3, F1),
                        Move(E3, F5)
                    ));
    }
}

TEST(Bishops, QuietMoves) {
    Position position = MakePosition(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . p . . . p . ."
            "5: . . . . . . . ."
            "4: . . . B . . . ."
            "3: . . . . . . . ."
            "2: . p . . . r . ."
            "1: . . . . . . . ."
            "   a b c d e f g h"
            //
            "   w KQkq - 0 1"
            );

    EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAre(
                    Move(D4, C5),
                    Move(D4, C3),
                    Move(D4, E5),
                    Move(D4, E3)
                ));
}

TEST(Bishops, Captures) {
    Position position = MakePosition(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . p . . . p . ."
            "5: . . . . . . . ."
            "4: . . . B . . . ."
            "3: . . . . . . . ."
            "2: . p . . . r . ."
            "1: . . . . . . . ."
            "   a b c d e f g h"
            //
            "   w KQkq - 12 20"
            );

    EXPECT_THAT(GenerateMoves<kCapture>(position), UnorderedElementsAre(
                    Move(D4, B6),
                    Move(D4, B2),
                    Move(D4, F6),
                    Move(D4, F2)
                ));
}

TEST(King, Evasions) {
    // N.B.: Evasions can still leave the king in check.
    {
        Position position = MakePosition(
                "8: . . . . . . . ."
                "7: . . . r . . . ."
                "6: . . . . . . . ."
                "5: . . . . . . . ."
                "4: . . . K . . . ."
                "3: . . . . . . . ."
                "2: . . . . . . . ."
                "1: . . . . . . . ."
                "   a b c d e f g h"
                //
                "   w KQkq - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kEvasion>(position), UnorderedElementsAre(
                        Move(D4, C5),
                        Move(D4, C4),
                        Move(D4, C3),
                        Move(D4, D5),
                        Move(D4, D3),
                        Move(D4, E5),
                        Move(D4, E4),
                        Move(D4, E3)
                    ));
    }
}

} // namespace
} // namespace chessengine
