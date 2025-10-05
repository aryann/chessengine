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

    Bitboard board;
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

TEST(Bitboard, ShiftNorth) {
    EXPECT_THAT(Bitboard(D4).Shift<kNorth>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . X . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(D8).Shift<kNorth>(), EqualsBitboard(
                    "8: . . . . . . . ."
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

TEST(Bitboard, ShiftNorthEast) {
    EXPECT_THAT(Bitboard(D4).Shift<kNorthEast>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . X . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(H8).Shift<kNorthEast>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(H7).Shift<kNorthEast>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(G8).Shift<kNorthEast>(), EqualsBitboard(
                    "8: . . . . . . . ."
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

TEST(Bitboard, ShiftEast) {
    EXPECT_THAT(Bitboard(D4).Shift<kEast>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . X . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(H4).Shift<kEast>(), EqualsBitboard(
                    "8: . . . . . . . ."
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

TEST(Bitboard, ShiftSouthEast) {
    EXPECT_THAT(Bitboard(D4).Shift<kSouthEast>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . X . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(H1).Shift<kSouthEast>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(H2).Shift<kSouthEast>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(G1).Shift<kSouthEast>(), EqualsBitboard(
                    "8: . . . . . . . ."
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

TEST(Bitboard, ShiftSouth) {
    EXPECT_THAT(Bitboard(D4).Shift<kSouth>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . X . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(D1).Shift<kSouth>(), EqualsBitboard(
                    "8: . . . . . . . ."
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

TEST(Bitboard, ShiftSouthWest) {
    EXPECT_THAT(Bitboard(D4).Shift<kSouthWest>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . X . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(A1).Shift<kSouthWest>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(B1).Shift<kSouthWest>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(A2).Shift<kSouthWest>(), EqualsBitboard(
                    "8: . . . . . . . ."
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

TEST(Bitboard, ShiftWest) {
    EXPECT_THAT(Bitboard(D4).Shift<kWest>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . X . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(A4).Shift<kWest>(), EqualsBitboard(
                    "8: . . . . . . . ."
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

TEST(Bitboard, ShiftNorthWest) {
    EXPECT_THAT(Bitboard(D4).Shift<kNorthWest>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . X . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(A8).Shift<kNorthWest>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(A7).Shift<kNorthWest>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(Bitboard(B8).Shift<kNorthWest>(), EqualsBitboard(
                    "8: . . . . . . . ."
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

TEST(Bitboard, LeastSignificantBit) {
    EXPECT_THAT(rank::k1.LeastSignificantBit(), Eq(A1));
    EXPECT_THAT(rank::k5.LeastSignificantBit(), Eq(A5));
    EXPECT_THAT(rank::k8.LeastSignificantBit(), Eq(A8));

    EXPECT_THAT(file::kA.LeastSignificantBit(), Eq(A8));
    EXPECT_THAT(file::kE.LeastSignificantBit(), Eq(E8));
    EXPECT_THAT(file::kH.LeastSignificantBit(), Eq(H8));

    EXPECT_THAT(Bitboard(0b1).LeastSignificantBit(), Eq(A8));
    EXPECT_THAT(Bitboard(0b10).LeastSignificantBit(), Eq(B8));
    EXPECT_THAT(Bitboard(0b11110).LeastSignificantBit(), Eq(B8));
    EXPECT_THAT(Bitboard(0b10011110).LeastSignificantBit(), Eq(B8));
    EXPECT_THAT(Bitboard(0b1111000).LeastSignificantBit(), Eq(D8));
}

TEST(Bitboard, PopLeastSignificantBit) {
    Bitboard board(0b10011110);

    EXPECT_THAT(board.Data(), Eq(0b10011110));
    EXPECT_THAT(board.PopLeastSignificantBit(), Eq(B8));
    EXPECT_THAT(board.Data(), Eq(0b10011100));
    EXPECT_THAT(board.PopLeastSignificantBit(), Eq(C8));
    EXPECT_THAT(board.Data(), Eq(0b10011000));
    EXPECT_THAT(board.PopLeastSignificantBit(), Eq(D8));
    EXPECT_THAT(board.Data(), Eq(0b10010000));
    EXPECT_THAT(board.PopLeastSignificantBit(), Eq(E8));
    EXPECT_THAT(board.Data(), Eq(0b10000000));
    EXPECT_THAT(board.PopLeastSignificantBit(), Eq(H8));
    EXPECT_THAT(board.Data(), Eq(0b00000000));

}

} // namespace
} // namespace chessengine

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
