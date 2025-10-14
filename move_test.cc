#include "move.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::Ne;
using ::testing::Not;

TEST(Move, Squares) {
    Move move(A1, B2);

    EXPECT_THAT(move.from(), Eq(A1));
    EXPECT_THAT(move.to(), Eq(B2));
}

TEST(Move, Equality) {
    EXPECT_THAT(Move(A1, A2), Eq(Move(A1, A2)));
    EXPECT_THAT(Move(A1, A2), Not(Eq(Move(H1, H2))));

    EXPECT_THAT(Move(A1, A2), Not(Ne(Move(A1, A2))));
    EXPECT_THAT(Move(A1, A2), Ne(Move(H1, H2)));
}

TEST(Move, CapturedPiece) {
    EXPECT_THAT(Move(A1, A2).GetCapturedPiece(), Eq(kEmptyPiece));
    EXPECT_THAT(Move(A1, A2, MoveOptions().SetCaptured(kPawn)).GetCapturedPiece(), Eq(kPawn));
    EXPECT_THAT(Move(A1, A2, MoveOptions().SetCaptured(kKnight)).GetCapturedPiece(), Eq(kKnight));
    EXPECT_THAT(Move(A1, A2, MoveOptions().SetCaptured(kBishop)).GetCapturedPiece(), Eq(kBishop));
    EXPECT_THAT(Move(A1, A2, MoveOptions().SetCaptured(kRook)).GetCapturedPiece(), Eq(kRook));
    EXPECT_THAT(Move(A1, A2, MoveOptions().SetCaptured(kKing)).GetCapturedPiece(), Eq(kKing));
}

} // namespace
} // namespace chessengine
