#include "move_generator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "position.h"
#include "testing.h"

namespace chessengine {
namespace {

using ::testing::AllOf;
using ::testing::Contains;
using ::testing::Eq;
using ::testing::IsEmpty;
using ::testing::Not;
using ::testing::UnorderedElementsAreArray;
using ::testing::UnorderedElementsAre;

TEST(GenerateMoves, QuietMoves_StartingPosition) {
    auto position = Position::Starting();

    EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAreArray(
                    MakeMoves({
                        "a2a3",
                        "a2a4",
                        "b1a3",
                        "b1c3",
                        "b2b3",
                        "b2b4",
                        "c2c3",
                        "c2c4",
                        "d2d3",
                        "d2d4",
                        "e2e3",
                        "e2e4",
                        "f2f3",
                        "f2f4",
                        "g1f3",
                        "g1h3",
                        "g2g3",
                        "g2g4",
                        "h2h3",
                        "h2h4",
                        })
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

    EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAreArray(
                    MakeMoves({
                        "a2a3",
                        "a2a4",
                        "b1a3",
                        "b1c3",
                        "b2b3",
                        "b2b4",
                        "c2c3",
                        "c2c4",
                        "d1e2",
                        "d1f3",
                        "d1g4",
                        "d1h5",
                        "d2d3",
                        "d2d4",
                        "e1e2",
                        "e4e5",
                        "f1a6",
                        "f1b5",
                        "f1c4",
                        "f1d3",
                        "f1e2",
                        "f2f3",
                        "f2f4",
                        "g1e2",
                        "g1f3",
                        "g1h3",
                        "g2g3",
                        "g2g4",
                        "h2h3",
                        "h2h4",
                        })
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
                "   w - - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAreArray(
                        MakeMoves({
                            "e7e8n",
                            "e7e8b",
                            "e7e8r",
                            "e7e8q",
                            })
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
                "   b - - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAreArray(
                        MakeMoves({
                            "a2a1n",
                            "a2a1b",
                            "a2a1r",
                            "a2a1q",
                            })
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
                "   w - - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kCapture>(position), UnorderedElementsAreArray(
                        MakeMoves({
                            "e3d4",
                            "e3f4",
                            })
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
                "   b - - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kCapture>(position), UnorderedElementsAreArray(
                        MakeMoves({
                            "d5c4",
                            "d5e4",
                            })
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
                "   w - - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAreArray(
                        MakeMoves({
                            "e3d5",
                            "e3f5",
                            "e3c4",
                            "e3g4",
                            "e3c2",
                            "e3g2",
                            "e3d1",
                            "e3f1",
                            })
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
                "   w - - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAreArray(
                        MakeMoves({
                            "e3c2",
                            "e3c4",
                            "e3g2",
                            "e3g4",
                            })
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
                "   w - - 0 1"
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
                "   w - - 12 20"
                );

        EXPECT_THAT(GenerateMoves<kCapture>(position), UnorderedElementsAreArray(
                        MakeMoves({
                            "e3d1",
                            "e3d5",
                            "e3f1",
                            "e3f5",
                            })
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
            "   w - - 0 1"
            );

    EXPECT_THAT(GenerateMoves<kQuiet>(position), UnorderedElementsAreArray(
                    MakeMoves({
                        "d4c5",
                        "d4c3",
                        "d4e5",
                        "d4e3",
                        })
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
            "   w - - 12 20"
            );

    EXPECT_THAT(GenerateMoves<kCapture>(position), UnorderedElementsAreArray(
                    MakeMoves({
                        "d4b6",
                        "d4b2",
                        "d4f6",
                        "d4f2",
                        })
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
                "   w - - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kEvasion>(position), UnorderedElementsAreArray(
                        MakeMoves({
                            "d4c5",
                            "d4c4",
                            "d4c3",
                            "d4d5",
                            "d4d3",
                            "d4e5",
                            "d4e4",
                            "d4e3",
                            })
                    ));
    }
}

TEST(Castling, WhiteCastling) {
    Position position = MakePosition(
            "8: r . . . k . . r"
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: . . . . . . . ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: R . . . K . . R"
            "   a b c d e f g h"
            //
            "   w KQ - 0 1"
            );

    EXPECT_THAT(GenerateMoves<kQuiet>(position), AllOf(
                    Contains(MakeMove("e1g1#c")),
                    Contains(MakeMove("e1c1#c"))
                ));
}

TEST(Castling, WhiteKingSideOnly) {
    Position position = MakePosition(
            "8: . . . . k . . r"
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: . . r . . . . ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: R . . . K . . R"
            "   a b c d e f g h"
            //
            "   w KQ - 0 1"
            );

    EXPECT_THAT(GenerateMoves<kQuiet>(position), AllOf(
                    Contains(MakeMove("e1g1#c")),
                    Not(Contains(MakeMove("e1c1#c")))
                ));
}

TEST(Castling, WhiteQueenSideOnly) {
    Position position = MakePosition(
            "8: r . . . k . . ."
            "7: . . . . . . . ."
            "6: . . . . . . r ."
            "5: . . . . . . . ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: R . . . K . . R"
            "   a b c d e f g h"
            //
            "   w KQ - 0 1"
            );

    EXPECT_THAT(GenerateMoves<kQuiet>(position), AllOf(
                    Contains(MakeMove("e1c1#c")),
                    Not(Contains(MakeMove("e1g1#c")))
                ));
}

TEST(Castling, Black) {
    Position position = MakePosition(
            "8: r . . . k . . r"
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: . . . . . . . ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: R . . . K . . R"
            "   a b c d e f g h"
            //
            "   b kq - 0 1"
            );

    EXPECT_THAT(GenerateMoves<kQuiet>(position), AllOf(
                    Contains(MakeMove("e8g8#c")),
                    Contains(MakeMove("e8c8#c"))
                ));
}

TEST(Castling, BlackKingSideOnly) {
    Position position = MakePosition(
            "8: r . . . k . . r"
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: . . . . . B . ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: R . . . K . . R"
            "   a b c d e f g h"
            //
            "   b kq - 0 1"
            );

    EXPECT_THAT(GenerateMoves<kQuiet>(position), AllOf(
                    Contains(MakeMove("e8g8#c")),
                    Not(Contains(MakeMove("e8c8#c")))
                ));
}

TEST(Castling, BlackQueenSideOnly) {
    Position position = MakePosition(
            "8: r . . . k . . r"
            "7: . . . . . . . ."
            "6: . . . . . . . N"
            "5: . . . . . . . ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: R . . . K . . R"
            "   a b c d e f g h"
            //
            "   b kq - 0 1"
            );

    EXPECT_THAT(GenerateMoves<kQuiet>(position), AllOf(
                    Contains(MakeMove("e8c8#c")),
                    Not(Contains(MakeMove("e8g8#c")))
                ));
}

TEST(Castling, None) {
    //
    {
        Position position = MakePosition(
                "8: r . . . k . . r"
                "7: . . . . . . . ."
                "6: . . . . . . . ."
                "5: . . . . . . . ."
                "4: . . . . . . . ."
                "3: . . . . . . . ."
                "2: . . . . . . . ."
                "1: R . . . K . . R"
                "   a b c d e f g h"
                //
                "   w - - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kQuiet>(position), AllOf(
                        Not(Contains(MakeMove("e1g1#c"))),
                        Not(Contains(MakeMove("e1c1#c")))
                    ));
    }
    //
    {
        Position position = MakePosition(
                "8: r . . . k . . r"
                "7: . . . . . . . ."
                "6: . . . . . . . ."
                "5: . . . . . . . ."
                "4: . . . . . . . ."
                "3: . . . . . . . ."
                "2: . . . . . . . ."
                "1: R . . . K . . R"
                "   a b c d e f g h"
                //
                "   b - - 0 1"
                );

        EXPECT_THAT(GenerateMoves<kQuiet>(position), AllOf(
                        Not(Contains(MakeMove("e8g8#c"))),
                        Not(Contains(MakeMove("e8c8#c")))
                    ));
    }
}

} // namespace
} // namespace chessengine
