#include "move.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::IsFalse;
using ::testing::IsTrue;

TEST(Move, Squares) {
    Move move(A1, B2);

    EXPECT_THAT(move.from(), Eq(A1));
    EXPECT_THAT(move.to(), Eq(B2));
}

TEST(Move, Equality) {
    EXPECT_THAT(Move(A1, A2) == Move(A1, A2), IsTrue());
    EXPECT_THAT(Move(A1, A2) == Move(H1, H2), IsFalse());

    EXPECT_THAT(Move(A1, A2) != Move(A1, A2), IsFalse());
    EXPECT_THAT(Move(A1, A2) != Move(H1, H2), IsTrue());
}

} // namespace
} // namespace chessengine
