#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "absl/strings/str_split.h"
#include "bitboard.h"
#include "testing.h"

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::IsFalse;
using ::testing::IsTrue;

TEST(Bitboard, Ranks) {
    EXPECT_THAT(rank::k1, EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: X X X X X X X X"
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(rank::k5, EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: X X X X X X X X"
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(rank::k8, EqualsBitboard(
                    "8: X X X X X X X X"
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(Bitboard, Files) {
    EXPECT_THAT(file::kA, EqualsBitboard(
                    "8: X . . . . . . ."
                    "7: X . . . . . . ."
                    "6: X . . . . . . ."
                    "5: X . . . . . . ."
                    "4: X . . . . . . ."
                    "3: X . . . . . . ."
                    "2: X . . . . . . ."
                    "1: X . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(file::kD, EqualsBitboard(
                    "8: . . . X . . . ."
                    "7: . . . X . . . ."
                    "6: . . . X . . . ."
                    "5: . . . X . . . ."
                    "4: . . . X . . . ."
                    "3: . . . X . . . ."
                    "2: . . . X . . . ."
                    "1: . . . X . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(file::kH, EqualsBitboard(
                    "8: . . . . . . . X"
                    "7: . . . . . . . X"
                    "6: . . . . . . . X"
                    "5: . . . . . . . X"
                    "4: . . . . . . . X"
                    "3: . . . . . . . X"
                    "2: . . . . . . . X"
                    "1: . . . . . . . X"
                    "   a b c d e f g h"
                ));
}

TEST(Bitboard, Corners) {
    Bitboard back_ranks = rank::k1 | rank::k8;

    Bitboard board = 0;
    board |= file::kA & back_ranks;
    board |= file::kH & back_ranks;

    EXPECT_THAT(board, EqualsBitboard(
                    "8: X . . . . . . X"
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: X . . . . . . X"
                    "   a b c d e f g h"
                ));
}

TEST(Bitboard, GetSetClear) {
    Bitboard board = rank::k1;

    EXPECT_THAT(Get(board, A1), IsTrue());
    EXPECT_THAT(Get(board, B1), IsTrue());
    EXPECT_THAT(Get(board, C1), IsTrue());
    EXPECT_THAT(Get(board, D1), IsTrue());
    EXPECT_THAT(Get(board, E1), IsTrue());
    EXPECT_THAT(Get(board, F1), IsTrue());
    EXPECT_THAT(Get(board, G1), IsTrue());
    EXPECT_THAT(Get(board, H1), IsTrue());

    EXPECT_THAT(Get(board, A2), IsFalse());
    EXPECT_THAT(Get(board, B3), IsFalse());
    EXPECT_THAT(Get(board, C4), IsFalse());
    EXPECT_THAT(Get(board, D5), IsFalse());
    EXPECT_THAT(Get(board, E6), IsFalse());
    EXPECT_THAT(Get(board, F7), IsFalse());
    EXPECT_THAT(Get(board, G8), IsFalse());
    EXPECT_THAT(Get(board, H8), IsFalse());

    board = Clear(board, B1);
    EXPECT_THAT(Get(board, B1), IsFalse());

    board = Set(board, B1);
    EXPECT_THAT(Get(board, B1), IsTrue());
}

} // namespace
} // namespace chessengine

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
