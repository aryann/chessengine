#include "move.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using testing::Eq;

TEST(Move, Squares) {
    Move move(A1, B2);

    EXPECT_THAT(move.from(), Eq(A1));
    EXPECT_THAT(move.to(), Eq(B2));
}

} // namespace
} // namespace chessengine
