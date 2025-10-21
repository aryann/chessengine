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
                    MakeMove("a2a3"),
                    MakeMove("a2a4"),
                    MakeMove("b1a3"),
                    MakeMove("b1c3"),
                    MakeMove("b2b3"),
                    MakeMove("b2b4"),
                    MakeMove("c2c3"),
                    MakeMove("c2c4"),
                    MakeMove("d2d3"),
                    MakeMove("d2d4"),
                    MakeMove("e2e3"),
                    MakeMove("e2e4"),
                    MakeMove("f2f3"),
                    MakeMove("f2f4"),
                    MakeMove("g1f3"),
                    MakeMove("g1h3"),
                    MakeMove("g2g3"),
                    MakeMove("g2g4"),
                    MakeMove("h2h3"),
                    MakeMove("h2h4")
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
                    MakeMove("a2a3"),
                    MakeMove("a2a4"),
                    MakeMove("b1a3"),
                    MakeMove("b1c3"),
                    MakeMove("b2b3"),
                    MakeMove("b2b4"),
                    MakeMove("c2c3"),
                    MakeMove("c2c4"),
                    MakeMove("d1e2"),
                    MakeMove("d1f3"),
                    MakeMove("d1g4"),
                    MakeMove("d1h5"),
                    MakeMove("d2d3"),
                    MakeMove("d2d4"),
                    MakeMove("e1e2"),
                    MakeMove("e4e5"),
                    MakeMove("f1a6"),
                    MakeMove("f1b5"),
                    MakeMove("f1c4"),
                    MakeMove("f1d3"),
                    MakeMove("f1e2"),
                    MakeMove("f2f3"),
                    MakeMove("f2f4"),
                    MakeMove("g1e2"),
                    MakeMove("g1f3"),
                    MakeMove("g1h3"),
                    MakeMove("g2g3"),
                    MakeMove("g2g4"),
                    MakeMove("h2h3"),
                    MakeMove("h2h4")
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
                        MakeMove("e7e8n"),
                        MakeMove("e7e8b"),
                        MakeMove("e7e8r"),
                        MakeMove("e7e8q")
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
                        MakeMove("a2a1n"),
                        MakeMove("a2a1b"),
                        MakeMove("a2a1r"),
                        MakeMove("a2a1q")
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
                        MakeMove("e3d4"),
                        MakeMove("e3f4")
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
                        MakeMove("d5c4"),
                        MakeMove("d5e4")
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
                        MakeMove("e3d5"),
                        MakeMove("e3f5"),
                        MakeMove("e3c4"),
                        MakeMove("e3g4"),
                        MakeMove("e3c2"),
                        MakeMove("e3g2"),
                        MakeMove("e3d1"),
                        MakeMove("e3f1")
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
                        MakeMove("e3c2"),
                        MakeMove("e3c4"),
                        MakeMove("e3g2"),
                        MakeMove("e3g4")
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
                        MakeMove("e3d1"),
                        MakeMove("e3d5"),
                        MakeMove("e3f1"),
                        MakeMove("e3f5")
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
                    MakeMove("d4c5"),
                    MakeMove("d4c3"),
                    MakeMove("d4e5"),
                    MakeMove("d4e3")
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
                    MakeMove("d4b6"),
                    MakeMove("d4b2"),
                    MakeMove("d4f6"),
                    MakeMove("d4f2")
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
                        MakeMove("d4c5"),
                        MakeMove("d4c4"),
                        MakeMove("d4c3"),
                        MakeMove("d4d5"),
                        MakeMove("d4d3"),
                        MakeMove("d4e5"),
                        MakeMove("d4e4"),
                        MakeMove("d4e3")
                    ));
    }
}

} // namespace
} // namespace chessengine
