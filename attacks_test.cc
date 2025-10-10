#include "attacks.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "testing.h"

namespace chessengine {
namespace {

using testing::Eq;

TEST(Attacks, WhitePawn) {
    EXPECT_THAT(kPseudoAttacks[kWhitePawn][A2], EqualsBitboard(
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
    EXPECT_THAT(kPseudoAttacks[kWhitePawn][B2], EqualsBitboard(
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
    EXPECT_THAT(kPseudoAttacks[kWhitePawn][H2], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kWhitePawn][A1], EqualsBitboard(
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
    EXPECT_THAT(kPseudoAttacks[kWhitePawn][E1], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kWhitePawn][A8], EqualsBitboard(
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
    EXPECT_THAT(kPseudoAttacks[kWhitePawn][H8], EqualsBitboard(
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
    EXPECT_THAT(kPseudoAttacks[kKnight][A1], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kKnight][H1], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kKnight][A8], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kKnight][H8], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kKnight][D4], EqualsBitboard(
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
    EXPECT_THAT(kPseudoAttacks[kBishop][D5], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kBishop][A1], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kBishop][H1], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kBishop][A8], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kBishop][H8], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kBishop][A5], EqualsBitboard(
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
    EXPECT_THAT(kPseudoAttacks[kRook][D5], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kRook][A1], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kRook][H8], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kRook][A5], EqualsBitboard(
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
    EXPECT_THAT(kPseudoAttacks[kQueen][D5], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kQueen][A1], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kQueen][H8], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kQueen][H1], EqualsBitboard(
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
    EXPECT_THAT(kPseudoAttacks[kKing][A1], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kKing][H1], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kKing][A8], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kKing][H8], EqualsBitboard(
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

    EXPECT_THAT(kPseudoAttacks[kKing][D5], EqualsBitboard(
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

TEST(GenerateBishopAttacks, All) {
    EXPECT_THAT(GenerateBishopAttacks(D5, Bitboard()), EqualsBitboard(
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

} // namespace
} // namespace chessengine

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
