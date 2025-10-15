#include "move.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::Ne;
using ::testing::Not;

TEST(Move, General) {
    //
    {
        Move move(A1, B2);

        EXPECT_THAT(move.from(), Eq(A1));
        EXPECT_THAT(move.to(), Eq(B2));
        EXPECT_THAT(move.GetCapturedPiece(), Eq(kEmptyPiece));
    }
    //
    {
        Move move(B1, C2, MoveOptions().SetCaptured(kPawn));

        EXPECT_THAT(move.from(), Eq(B1));
        EXPECT_THAT(move.to(), Eq(C2));
        EXPECT_THAT(move.GetCapturedPiece(), Eq(kPawn));
    }
    //
    {
        Move move(A7, B8, MoveOptions().SetCaptured(kKnight));

        EXPECT_THAT(move.from(), Eq(A7));
        EXPECT_THAT(move.to(), Eq(B8));
        EXPECT_THAT(move.GetCapturedPiece(), Eq(kKnight));
    }
    //
    {
        Move move(A1, B2, MoveOptions().SetCaptured(kBishop));

        EXPECT_THAT(move.from(), Eq(A1));
        EXPECT_THAT(move.to(), Eq(B2));
        EXPECT_THAT(move.GetCapturedPiece(), Eq(kBishop));
    }
    //
    {
        Move move(A1, B2, MoveOptions().SetCaptured(kRook));

        EXPECT_THAT(move.from(), Eq(A1));
        EXPECT_THAT(move.to(), Eq(B2));
        EXPECT_THAT(move.GetCapturedPiece(), Eq(kRook));
    }
    //
    {
        Move move(H1, A1, MoveOptions().SetCaptured(kKing));

        EXPECT_THAT(move.from(), Eq(H1));
        EXPECT_THAT(move.to(), Eq(A1));
        EXPECT_THAT(move.GetCapturedPiece(), Eq(kKing));
    }
}

TEST(Move, Equality) {
    EXPECT_THAT(Move(A1, A2), Eq(Move(A1, A2)));
    EXPECT_THAT(Move(A1, A2), Not(Eq(Move(H1, H2))));

    EXPECT_THAT(Move(A1, A2), Not(Ne(Move(A1, A2))));
    EXPECT_THAT(Move(A1, A2), Ne(Move(H1, H2)));
}

} // namespace
} // namespace chessengine
