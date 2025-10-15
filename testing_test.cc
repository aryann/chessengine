#include "testing.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "testing.h"

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::Optional;

TEST(TestPositionToFen, Ok) {
    EXPECT_THAT(TestPositionToFen(
                    "8: r n b q k b n r\n"
                    "7: p p p p p p p p\n"
                    "6: . . . . . . . .\n"
                    "5: . . . . . . . .\n"
                    "4: . . . . . . . .\n"
                    "3: . . . . . . . .\n"
                    "2: P P P P P P P P\n"
                    "1: R N B Q K B N R\n"
                    "   a b c d e f g h\n"
                    "\n"
                    "   w KQkq - 0 1\n"
                ), Eq("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));

    EXPECT_THAT(TestPositionToFen(
                    "8: r . . . k . . r"
                    "7: p . p p q p b ."
                    "6: b n . . p n p ."
                    "5: . . . P N . . ."
                    "4: . p . . P . . ."
                    "3: . . N . . Q . p"
                    "2: P P P B B P P P"
                    "1: R . . . K . . R"
                    "   a b c d e f g h"
                    ""
                    "   w KQkq - 0 1"
                ), Eq("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"));

    EXPECT_THAT(TestPositionToFen(
                    "8: . . . . . . . ."
                    "7: . . p . . . . ."
                    "6: . . . p . . . ."
                    "5: K P . . . . . r"
                    "4: . R . . . p . k"
                    "3: . . . . . . . ."
                    "2: . . . . P . P ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                    //
                    "   w - a3 0 1"
                ), Eq("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - a3 0 1"));
}

TEST(TestPositionToFen, Failures) {
    ASSERT_DEATH(TestPositionToFen(""), "Invalid position input: ");
    ASSERT_DEATH(TestPositionToFen("KQkq"), "Invalid position input: KQkq");
}

} // namespace
} // namespace chessengine
