#include "attacks.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "testing.h"

namespace chessengine {
namespace {

using testing::Eq;

TEST(Attacks, WhitePawn) {
    EXPECT_THAT(kPawnAttacks[kWhite][A2], EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . X . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(kPawnAttacks[kWhite][B2], EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: X . X . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(kPawnAttacks[kWhite][H2], EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . X ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    // The first-rank attacks will never be called, but for implementation simplicity,
    // we still calculate them.
    EXPECT_THAT(kPawnAttacks[kWhite][A1], EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . X . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(kPawnAttacks[kWhite][E1], EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . X . X . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(kPawnAttacks[kWhite][A8], EqualsBitboard(
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
    EXPECT_THAT(kPawnAttacks[kWhite][H8], EqualsBitboard(
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

TEST(Attacks, BlackPawn) {
    EXPECT_THAT(kPawnAttacks[kBlack][A7], EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . X . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(kPawnAttacks[kBlack][B7], EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: X . X . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(kPawnAttacks[kBlack][H7], EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . X ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    // The eighth-rank attacks will never be called, but for implementation simplicity,
    // we still calculate them.
    EXPECT_THAT(kPawnAttacks[kBlack][A8], EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . X . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(kPawnAttacks[kBlack][E8], EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . X . X . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(kPawnAttacks[kBlack][A1], EqualsBitboard(
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
    EXPECT_THAT(kPawnAttacks[kBlack][H1], EqualsBitboard(
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

TEST(Attacks, Knight) {
    EXPECT_THAT(GenerateAttacks<kKnight>(A1, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . X . . . . . ."
                    "2: . . X . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kKnight>(H1, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . X ."
                    "2: . . . . . X . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kKnight>(A8, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . X . . . . ."
                    "6: . X . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kKnight>(H8, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . X . ."
                    "6: . . . . . . X ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kKnight>(D4, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . X . X . . ."
                    "5: . X . . . X . ."
                    "4: . . . . . . . ."
                    "3: . X . . . X . ."
                    "2: . . X . X . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(Attacks, Bishop) {
    EXPECT_THAT(GenerateAttacks<kBishop>(D5, kEmptyBoard), EqualsBitboard(
                    "8: X . . . . . X ."
                    "7: . X . . . X . ."
                    "6: . . X . X . . ."
                    "5: . . . . . . . ."
                    "4: . . X . X . . ."
                    "3: . X . . . X . ."
                    "2: X . . . . . X ."
                    "1: . . . . . . . X"
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kBishop>(A1, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . . X"
                    "7: . . . . . . X ."
                    "6: . . . . . X . ."
                    "5: . . . . X . . ."
                    "4: . . . X . . . ."
                    "3: . . X . . . . ."
                    "2: . X . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kBishop>(H1, kEmptyBoard), EqualsBitboard(
                    "8: X . . . . . . ."
                    "7: . X . . . . . ."
                    "6: . . X . . . . ."
                    "5: . . . X . . . ."
                    "4: . . . . X . . ."
                    "3: . . . . . X . ."
                    "2: . . . . . . X ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kBishop>(A8, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . X . . . . . ."
                    "6: . . X . . . . ."
                    "5: . . . X . . . ."
                    "4: . . . . X . . ."
                    "3: . . . . . X . ."
                    "2: . . . . . . X ."
                    "1: . . . . . . . X"
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kBishop>(H8, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . X ."
                    "6: . . . . . X . ."
                    "5: . . . . X . . ."
                    "4: . . . X . . . ."
                    "3: . . X . . . . ."
                    "2: . X . . . . . ."
                    "1: X . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kBishop>(A5, kEmptyBoard), EqualsBitboard(
                    "8: . . . X . . . ."
                    "7: . . X . . . . ."
                    "6: . X . . . . . ."
                    "5: . . . . . . . ."
                    "4: . X . . . . . ."
                    "3: . . X . . . . ."
                    "2: . . . X . . . ."
                    "1: . . . . X . . ."
                    "   a b c d e f g h"
                ));
}

TEST(Attacks, Rook) {
    EXPECT_THAT(GenerateAttacks<kRook>(D5, kEmptyBoard), EqualsBitboard(
                    "8: . . . X . . . ."
                    "7: . . . X . . . ."
                    "6: . . . X . . . ."
                    "5: X X X . X X X X"
                    "4: . . . X . . . ."
                    "3: . . . X . . . ."
                    "2: . . . X . . . ."
                    "1: . . . X . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kRook>(A1, kEmptyBoard), EqualsBitboard(
                    "8: X . . . . . . ."
                    "7: X . . . . . . ."
                    "6: X . . . . . . ."
                    "5: X . . . . . . ."
                    "4: X . . . . . . ."
                    "3: X . . . . . . ."
                    "2: X . . . . . . ."
                    "1: . X X X X X X X"
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kRook>(H8, kEmptyBoard), EqualsBitboard(
                    "8: X X X X X X X ."
                    "7: . . . . . . . X"
                    "6: . . . . . . . X"
                    "5: . . . . . . . X"
                    "4: . . . . . . . X"
                    "3: . . . . . . . X"
                    "2: . . . . . . . X"
                    "1: . . . . . . . X"
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kRook>(A5, kEmptyBoard), EqualsBitboard(
                    "8: X . . . . . . ."
                    "7: X . . . . . . ."
                    "6: X . . . . . . ."
                    "5: . X X X X X X X"
                    "4: X . . . . . . ."
                    "3: X . . . . . . ."
                    "2: X . . . . . . ."
                    "1: X . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(Attacks, Queen) {
    EXPECT_THAT(GenerateAttacks<kQueen>(D5, kEmptyBoard), EqualsBitboard(
                    "8: X . . X . . X ."
                    "7: . X . X . X . ."
                    "6: . . X X X . . ."
                    "5: X X X . X X X X"
                    "4: . . X X X . . ."
                    "3: . X . X . X . ."
                    "2: X . . X . . X ."
                    "1: . . . X . . . X"
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kQueen>(A1, kEmptyBoard), EqualsBitboard(
                    "8: X . . . . . . X"
                    "7: X . . . . . X ."
                    "6: X . . . . X . ."
                    "5: X . . . X . . ."
                    "4: X . . X . . . ."
                    "3: X . X . . . . ."
                    "2: X X . . . . . ."
                    "1: . X X X X X X X"
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kQueen>(H8, kEmptyBoard), EqualsBitboard(
                    "8: X X X X X X X ."
                    "7: . . . . . . X X"
                    "6: . . . . . X . X"
                    "5: . . . . X . . X"
                    "4: . . . X . . . X"
                    "3: . . X . . . . X"
                    "2: . X . . . . . X"
                    "1: X . . . . . . X"
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kQueen>(H1, kEmptyBoard), EqualsBitboard(
                    "8: X . . . . . . X"
                    "7: . X . . . . . X"
                    "6: . . X . . . . X"
                    "5: . . . X . . . X"
                    "4: . . . . X . . X"
                    "3: . . . . . X . X"
                    "2: . . . . . . X X"
                    "1: X X X X X X X ."
                    "   a b c d e f g h"
                ));
}

TEST(Attacks, King) {
    EXPECT_THAT(GenerateAttacks<kKing>(A1, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: X X . . . . . ."
                    "1: . X . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kKing>(H1, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . X X"
                    "1: . . . . . . X ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kKing>(A8, kEmptyBoard), EqualsBitboard(
                    "8: . X . . . . . ."
                    "7: X X . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kKing>(H8, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . X ."
                    "7: . . . . . . X X"
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GenerateAttacks<kKing>(D5, kEmptyBoard), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . X X X . . ."
                    "5: . . X . X . . ."
                    "4: . . X X X . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GenerateBishopAttacks, NoBlockers) {
    Bitboard blockers;
    EXPECT_THAT(GenerateAttacks<kBishop>(D5, blockers), EqualsBitboard(
                    "8: X . . . . . X ."
                    "7: . X . . . X . ."
                    "6: . . X . X . . ."
                    "5: . . . . . . . ."
                    "4: . . X . X . . ."
                    "3: . X . . . X . ."
                    "2: X . . . . . X ."
                    "1: . . . . . . . X"
                    "   a b c d e f g h"
                ));
}

TEST(GenerateBishopAttacks, AllPathsBlocked) {
    Bitboard blockers(
            "8: X . . . . . X ."
            "7: . X . . . X . ."
            "6: . . X . X . . ."
            "5: . . . . . . . ."
            "4: . . X . X . . ."
            "3: . X . . . X . ."
            "2: X . . . . . X ."
            "1: . . . . . . . X"
            "   a b c d e f g h"
            );

    EXPECT_THAT(GenerateAttacks<kBishop>(D5, blockers), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . X . X . . ."
                    "5: . . . . . . . ."
                    "4: . . X . X . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GenerateBishopAttacks, EdgesBlockedOnly) {
    Bitboard blockers(
            "8: X . . . . . X ."
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: . . . . . . . ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: X . . . . . . ."
            "1: . . . . . . . X"
            "   a b c d e f g h"
            );

    EXPECT_THAT(GenerateAttacks<kBishop>(D5, blockers), EqualsBitboard(
                    "8: X . . . . . X ."
                    "7: . X . . . X . ."
                    "6: . . X . X . . ."
                    "5: . . . . . . . ."
                    "4: . . X . X . . ."
                    "3: . X . . . X . ."
                    "2: X . . . . . X ."
                    "1: . . . . . . . X"
                    "   a b c d e f g h"
                ));
}

TEST(BishopAttacksTest, PieceOnCornerA1) {
    Bitboard blockers;
    EXPECT_THAT(GenerateAttacks<kBishop>(A1, blockers), EqualsBitboard(
                    "8: . . . . . . . X"
                    "7: . . . . . . X ."
                    "6: . . . . . X . ."
                    "5: . . . . X . . ."
                    "4: . . . X . . . ."
                    "3: . . X . . . . ."
                    "2: . X . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(BishopAttacksTest, PieceOnEdgeA4) {
    Bitboard blockers;
    EXPECT_THAT(GenerateAttacks<kBishop>(A4, blockers), EqualsBitboard(
                    "8: . . . . X . . ."
                    "7: . . . X . . . ."
                    "6: . . X . . . . ."
                    "5: . X . . . . . ."
                    "4: . . . . . . . ."
                    "3: . X . . . . . ."
                    "2: . . X . . . . ."
                    "1: . . . X . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GenerateRookAttacks, NoBlockers) {
    Bitboard blockers;

    EXPECT_THAT(GenerateAttacks<kRook>(D5, blockers), EqualsBitboard(
                    "8: . . . X . . . ."
                    "7: . . . X . . . ."
                    "6: . . . X . . . ."
                    "5: X X X . X X X X"
                    "4: . . . X . . . ."
                    "3: . . . X . . . ."
                    "2: . . . X . . . ."
                    "1: . . . X . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GenerateRookAttacks, AllPathsBlocked) {
    Bitboard blockers(
            "8: . . . X . . . ."
            "7: . . . X . . . ."
            "6: . . . X . . . ."
            "5: X X X . X X X X"
            "4: . . . X . . . ."
            "3: . . . X . . . ."
            "2: . . . X . . . ."
            "1: . . . X . . . ."
            "   a b c d e f g h"
            );

    EXPECT_THAT(GenerateAttacks<kRook>(D5, blockers), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . X . . . ."
                    "5: . . X . X . . ."
                    "4: . . . X . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GenerateRookAttacks, EdgesBlockedOnly) {
    Bitboard blockers(
            "8: . . . X . . . ."
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: X . . . . . . X"
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: . . . X . . . ."
            "   a b c d e f g h"
            );

    EXPECT_THAT(GenerateAttacks<kRook>(D5, blockers), EqualsBitboard(
                    "8: . . . X . . . ."
                    "7: . . . X . . . ."
                    "6: . . . X . . . ."
                    "5: X X X . X X X X"
                    "4: . . . X . . . ."
                    "3: . . . X . . . ."
                    "2: . . . X . . . ."
                    "1: . . . X . . . ."
                    "   a b c d e f g h"
                ));
}


TEST(RookAttacksTest, PieceOnCornerH1) {
    Bitboard blockers;

    EXPECT_THAT(GenerateAttacks<kRook>(H1, blockers), EqualsBitboard(
                    "8: . . . . . . . X"
                    "7: . . . . . . . X"
                    "6: . . . . . . . X"
                    "5: . . . . . . . X"
                    "4: . . . . . . . X"
                    "3: . . . . . . . X"
                    "2: . . . . . . . X"
                    "1: X X X X X X X ."
                    "   a b c d e f g h"
                ));
}

TEST(RookAttacksTest, PieceOnEdgeA4) {
    Bitboard blockers;

    EXPECT_THAT(GenerateAttacks<kRook>(A4, blockers), EqualsBitboard(
                    "8: X . . . . . . ."
                    "7: X . . . . . . ."
                    "6: X . . . . . . ."
                    "5: X . . . . . . ."
                    "4: . X X X X X X X"
                    "3: X . . . . . . ."
                    "2: X . . . . . . ."
                    "1: X . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(RookAttacksTest, MultipleBlockersOnSameRay) {
    Bitboard blockers(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: . . . . X . X ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: . . . . . . . ."
            "   a b c d e f g h"
            );
    EXPECT_THAT(GenerateAttacks<kRook>(D5, blockers), EqualsBitboard(
                    "8: . . . X . . . ."
                    "7: . . . X . . . ."
                    "6: . . . X . . . ."
                    "5: X X X . X . . ."
                    "4: . . . X . . . ."
                    "3: . . . X . . . ."
                    "2: . . . X . . . ."
                    "1: . . . X . . . ."
                    "   a b c d e f g h"
                ));
}

} // namespace
} // namespace chessengine

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
