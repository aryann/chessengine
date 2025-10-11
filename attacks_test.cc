#include "attacks.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "testing.h"

namespace chessengine {
namespace {

using testing::Eq;

TEST(MakeRay, North_CenterBoardRay) {
    EXPECT_THAT(MakeRay<kNorth>(E4), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . X . . ."
                    "6: . . . . X . . ."
                    "5: . . . . X . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(MakeRay, North_ZeroLengthRayFromRank7) {
    EXPECT_THAT(MakeRay<kNorth>(D7), EqualsBitboard(
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

TEST(MakeRay, South_CenterBoardRay) {
    EXPECT_THAT(MakeRay<kSouth>(D5), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . X . . . ."
                    "3: . . . X . . . ."
                    "2: . . . X . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(MakeRay, South_ZeroLengthRayFromRank2) {
    EXPECT_THAT(MakeRay<kSouth>(A2), EqualsBitboard(
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

TEST(MakeRay, East_LongRayFromAFile) {
    EXPECT_THAT(MakeRay<kEast>(A1), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . X X X X X X ."
                    "   a b c d e f g h"
                ));
}

TEST(MakeRay, East_ZeroLengthRayFromGFile) {
    EXPECT_THAT(MakeRay<kEast>(G6), EqualsBitboard(
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

TEST(MakeRay, West_LongRayFromHFile) {
    EXPECT_THAT(MakeRay<kWest>(H8), EqualsBitboard(
                    "8: . X X X X X X ."
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

TEST(MakeRay, West_ZeroLengthRayFromBFile) {
    EXPECT_THAT(MakeRay<kWest>(B4), EqualsBitboard(
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

TEST(MakeRay, NorthEast_LongRayFromCorner) {
    EXPECT_THAT(MakeRay<kNorthEast>(A1), EqualsBitboard(
                    "8: . . . . . . . ."
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

TEST(MakeRay, NorthEast_ZeroLengthRayFromRank7) {
    EXPECT_THAT(MakeRay<kNorthEast>(F7), EqualsBitboard(
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

TEST(MakeRay, NorthEast_ZeroLengthRayFromGFile) {
    EXPECT_THAT(MakeRay<kNorthEast>(G5), EqualsBitboard(
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

TEST(MakeRay, NorthWest_LongRayFromCorner) {
    EXPECT_THAT(MakeRay<kNorthWest>(H1), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . X . . . . . ."
                    "6: . . X . . . . ."
                    "5: . . . X . . . ."
                    "4: . . . . X . . ."
                    "3: . . . . . X . ."
                    "2: . . . . . . X ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(MakeRay, NorthWest_ZeroLengthRayFromB7) {
    EXPECT_THAT(MakeRay<kNorthWest>(B7), EqualsBitboard(
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

TEST(MakeRay, SouthEast_LongRayFromCorner) {
    EXPECT_THAT(MakeRay<kSouthEast>(A8), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . X . . . . . ."
                    "6: . . X . . . . ."
                    "5: . . . X . . . ."
                    "4: . . . . X . . ."
                    "3: . . . . . X . ."
                    "2: . . . . . . X ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(MakeRay, SouthEast_ZeroLengthRayFromG2) {
    EXPECT_THAT(MakeRay<kSouthEast>(G2), EqualsBitboard(
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

TEST(MakeRay, SouthWest_LongRayFromCorner) {
    EXPECT_THAT(MakeRay<kSouthWest>(H8), EqualsBitboard(
                    "8: . . . . . . . ."
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

TEST(MakeRay, SouthWest_ZeroLengthRayFromB2) {
    EXPECT_THAT(MakeRay<kSouthWest>(B2), EqualsBitboard(
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

//================================================================================
// Bishop Attack Tests
//================================================================================

TEST(GenerateBishopAttacks, Center_NoBlockers) {
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

TEST(GenerateBishopAttacks, Center_AdjacentBlockers) {
    Bitboard blockers(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . . X . X . . ."
            "5: . . . . . . . ."
            "4: . . X . X . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: . . . . . . . ."
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

TEST(GenerateBishopAttacks, Center_DistantBlockers) {
    Bitboard blockers(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: . . . . . . . ."
            "4: . . . . . . . ."
            "3: . X . . . . . ."
            "2: . . . . . . X ."
            "1: . . . . . . . ."
            "   a b c d e f g h"
            );

    EXPECT_THAT(GenerateAttacks<kBishop>(D5, blockers), EqualsBitboard(
                    "8: X . . . . . X ."
                    "7: . X . . . X . ."
                    "6: . . X . X . . ."
                    "5: . . . . . . . ."
                    "4: . . X . X . . ."
                    "3: . X . . . X . ."
                    "2: . . . . . . X ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GenerateBishopAttacks, CornerA1_NoBlockers) {
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

TEST(GenerateBishopAttacks, CornerA1_WithBlocker) {
    Bitboard blockers(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: . . . . . . . ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . X . . . . . ."
            "1: . . . . . . . ."
            "   a b c d e f g h"
            );

    EXPECT_THAT(GenerateAttacks<kBishop>(A1, blockers), EqualsBitboard(
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
}

TEST(GenerateBishopAttacks, EdgeA4_NoBlockers) {
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

//================================================================================
// Rook Attack Tests
//================================================================================

TEST(GenerateRookAttacks, Center_NoBlockers) {
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

TEST(GenerateRookAttacks, Center_AdjacentBlockers) {
    Bitboard blockers(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . . . X . . . ."
            "5: . . X . X . . ."
            "4: . . . X . . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: . . . . . . . ."
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

TEST(GenerateRookAttacks, Center_MultipleBlockersOnRay) {
    Bitboard blockers(
            "8: . . . . . . . ."
            "7: . . . X . . . ."
            "6: . . . . . . . ."
            "5: . X . . X . X ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . . . X . . . ."
            "1: . . . . . . . ."
            "   a b c d e f g h"
            );

    EXPECT_THAT(GenerateAttacks<kRook>(D5, blockers), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . X . . . ."
                    "6: . . . X . . . ."
                    "5: . X X . X . . ."
                    "4: . . . X . . . ."
                    "3: . . . X . . . ."
                    "2: . . . X . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GenerateRookAttacks, CornerA1_NoBlockers) {
    Bitboard blockers;

    EXPECT_THAT(GenerateAttacks<kRook>(A1, blockers), EqualsBitboard(
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
}

TEST(GenerateRookAttacks, CornerA1_WithBlockers) {
    Bitboard blockers(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: . . . . . . . ."
            "4: X . . . . . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: . . . X . . . ."
            "   a b c d e f g h"
            );

    EXPECT_THAT(GenerateAttacks<kRook>(A1, blockers), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: X . . . . . . ."
                    "3: X . . . . . . ."
                    "2: X . . . . . . ."
                    "1: . X X X . . . ."
                    "   a b c d e f g h"
                ));
}

//================================================================================
// Queen Attack Tests
//================================================================================

TEST(GenerateQueenAttacks, Center_NoBlockers) {
    Bitboard blockers;

    EXPECT_THAT(GenerateAttacks<kQueen>(D5, blockers), EqualsBitboard(
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
}

TEST(GenerateQueenAttacks, Center_WithBlockers) {
    Bitboard blockers(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . . X . . . . ."
            "5: . . . . . . . ."
            "4: . . . X . . . ."
            "3: . . . . . X . ."
            "2: . . . . . . . ."
            "1: . . . . . . . ."
            "   a b c d e f g h"
            );

    EXPECT_THAT(GenerateAttacks<kQueen>(D5, blockers), EqualsBitboard(
                    "8: . . . X . . X ."
                    "7: . . . X . X . ."
                    "6: . . X X X . . ."
                    "5: X X X . X X X X"
                    "4: . . X X X . . ."
                    "3: . X . . . X . ."
                    "2: X . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GenerateQueenAttacks, CornerA1_NoBlockers) {
    Bitboard blockers;

    EXPECT_THAT(GenerateAttacks<kQueen>(A1, blockers), EqualsBitboard(
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
}

TEST(GenerateQueenAttacks, Surrounded) {
    Bitboard blockers(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . . X X X . . ."
            "5: . . X . X . . ."
            "4: . . X X X . . ."
            "3: . . . . . . . ."
            "2: . . . . . . . ."
            "1: . . . . . . . ."
            "   a b c d e f g h"
            );


    EXPECT_THAT(GenerateAttacks<kQueen>(D5, blockers), EqualsBitboard(
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

} // namespace
} // namespace chessengine

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
