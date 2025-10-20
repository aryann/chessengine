#include "move.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::IsTrue;
using ::testing::IsFalse;
using ::testing::Ne;
using ::testing::Not;

TEST(Move, NonPromotion) {
    Move move(A1, B2);

    EXPECT_THAT(move.from(), Eq(A1));
    EXPECT_THAT(move.to(), Eq(B2));
    EXPECT_THAT(move.IsPromotion(), IsFalse());
}

TEST(Move, Promotion) {
    //
    {
        Move move(A7, A8, kKnight);

        EXPECT_THAT(move.from(), Eq(A7));
        EXPECT_THAT(move.to(), Eq(A8));
        EXPECT_THAT(move.IsPromotion(), IsTrue());
        EXPECT_THAT(move.GetPromotedPiece(), Eq(kKnight));
    }
    //
    {
        Move move(A7, A8, kBishop);

        EXPECT_THAT(move.from(), Eq(A7));
        EXPECT_THAT(move.to(), Eq(A8));
        EXPECT_THAT(move.IsPromotion(), IsTrue());
        EXPECT_THAT(move.GetPromotedPiece(), Eq(kBishop));
    }
    //
    {
        Move move(A7, A8, kRook);

        EXPECT_THAT(move.from(), Eq(A7));
        EXPECT_THAT(move.to(), Eq(A8));
        EXPECT_THAT(move.IsPromotion(), IsTrue());
        EXPECT_THAT(move.GetPromotedPiece(), Eq(kRook));
    }
    //
    {
        Move move(A7, A8, kQueen);

        EXPECT_THAT(move.from(), Eq(A7));
        EXPECT_THAT(move.to(), Eq(A8));
        EXPECT_THAT(move.IsPromotion(), IsTrue());
        EXPECT_THAT(move.GetPromotedPiece(), Eq(kQueen));
    }
}

TEST(Move, Equality) {
    EXPECT_THAT(Move(A1, A2), Eq(Move(A1, A2)));
    EXPECT_THAT(Move(A7, A8, kKnight), Eq(Move(A7, A8, kKnight)));
    EXPECT_THAT(Move(A7, A8, kKnight), Not(Eq(Move(A7, A8, kBishop))));
    EXPECT_THAT(Move(A1, A2), Not(Eq(Move(H1, H2))));

    EXPECT_THAT(Move(A1, A2), Not(Ne(Move(A1, A2))));
    EXPECT_THAT(Move(A1, A2), Ne(Move(H1, H2)));
}

} // namespace
} // namespace chessengine
