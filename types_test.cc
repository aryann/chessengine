#include "types.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using ::testing::Eq;

TEST(Square, ToString) {
    EXPECT_THAT(ToString(A8), Eq("A8"));
    EXPECT_THAT(ToString(H1), Eq("H1"));
    EXPECT_THAT(ToString(D5), Eq("D5"));
    EXPECT_THAT(ToString(A1), Eq("A1"));
    EXPECT_THAT(ToString(H1), Eq("H1"));

    EXPECT_THAT(ToString(kNumSquares), Eq("kNumSquares"));
}

} // namespace
} // namespace chessengine

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
