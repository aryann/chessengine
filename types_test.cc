#include "types.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "testing.h"

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::Not;


TEST(Square, FromString) {
    EXPECT_THAT(FromString("a8"), IsExpectedValue(A7));
    //EXPECT_THAT("a", Eq("b"));
    //EXPECT_THAT(FromString("a8").value(), Eq(A7));

}

TEST(Square, ToString) {
    EXPECT_THAT(ToString(A8), Eq("a8"));
    EXPECT_THAT(ToString(H1), Eq("h1"));
    EXPECT_THAT(ToString(D5), Eq("d5"));
    EXPECT_THAT(ToString(A1), Eq("a1"));
    EXPECT_THAT(ToString(H1), Eq("h1"));
}

} // namespace
} // namespace chessengine

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
