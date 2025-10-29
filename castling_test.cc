#include "castling.h"

#include <format>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "testing.h"

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::IsFalse;
using ::testing::IsTrue;

TEST(Constructor, NoRights) {
    CastlingRights rights;

    EXPECT_THAT(std::format("{}", rights), Eq("-"));
    EXPECT_THAT(rights.HasKingSide<kWhite>(), IsFalse());
    EXPECT_THAT(rights.HasQueenSide<kWhite>(), IsFalse());
    EXPECT_THAT(rights.HasKingSide<kBlack>(), IsFalse());
    EXPECT_THAT(rights.HasQueenSide<kBlack>(), IsFalse());
}

TEST(Constructor, AllRights) {
    CastlingRights rights(kAllCastlingRights);

    EXPECT_THAT(std::format("{}", rights), Eq("KQkq"));
    EXPECT_THAT(rights.HasKingSide<kWhite>(), IsTrue());
    EXPECT_THAT(rights.HasQueenSide<kWhite>(), IsTrue());
    EXPECT_THAT(rights.HasKingSide<kBlack>(), IsTrue());
    EXPECT_THAT(rights.HasQueenSide<kBlack>(), IsTrue());
}

TEST(InvalidateOnMove, RookMoves) {
    CastlingRights rights(kAllCastlingRights);

    EXPECT_THAT(std::format("{}", rights), Eq("KQkq"));

    rights.InvalidateOnMove(A1);
    EXPECT_THAT(std::format("{}", rights), Eq("Kkq"));

    rights.InvalidateOnMove(H1);
    EXPECT_THAT(std::format("{}", rights), Eq("kq"));

    rights.InvalidateOnMove(A8);
    EXPECT_THAT(std::format("{}", rights), Eq("k"));

    rights.InvalidateOnMove(H8);
    EXPECT_THAT(std::format("{}", rights), Eq("-"));
}

TEST(InvalidateOnMove, KingMoves) {
    CastlingRights rights(kAllCastlingRights);

    EXPECT_THAT(std::format("{}", rights), Eq("KQkq"));

    rights.InvalidateOnMove(E1);
    EXPECT_THAT(std::format("{}", rights), Eq("kq"));

    rights.InvalidateOnMove(E8);
    EXPECT_THAT(std::format("{}", rights), Eq("-"));
}

TEST(GetKingSideCastlingPath, White) {
    EXPECT_THAT(GetKingSideCastlingPath<kWhite>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . X X ."
                    "   a b c d e f g h"
                ));
}

TEST(GetKingSideCastlingPath, Black) {
    EXPECT_THAT(GetKingSideCastlingPath<kBlack>(), EqualsBitboard(
                    "8: . . . . . X X ."
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

TEST(GetQueenSideCastlingPath, White) {
    EXPECT_THAT(GetQueenSideCastlingPath<kWhite>(), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . X X X . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GetQueenSideCastlingPath, Black) {
    EXPECT_THAT(GetQueenSideCastlingPath<kBlack>(), EqualsBitboard(
                    "8: . X X X . . . ."
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

} // namespace
} // namespace chessengine
