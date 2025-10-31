#include "types.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>

#include "testing.h"

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::Optional;

TEST(Square, ParseSquare) {
  EXPECT_THAT(ParseSquare("a8"), Optional(Eq(A8)));
  EXPECT_THAT(ParseSquare("h8"), Optional(Eq(H8)));
  EXPECT_THAT(ParseSquare("d5"), Optional(Eq(D5)));
  EXPECT_THAT(ParseSquare("a1"), Optional(Eq(A1)));
  EXPECT_THAT(ParseSquare("d1"), Optional(Eq(D1)));
  EXPECT_THAT(ParseSquare("h1"), Optional(Eq(H1)));

  EXPECT_THAT(ParseSquare("aa8"), Eq(std::nullopt));
  EXPECT_THAT(ParseSquare("h11"), Eq(std::nullopt));
  EXPECT_THAT(ParseSquare("A1"), Eq(std::nullopt));
  EXPECT_THAT(ParseSquare("a"), Eq(std::nullopt));
  EXPECT_THAT(ParseSquare(""), Eq(std::nullopt));
}

TEST(Square, ToString) {
  EXPECT_THAT(ToString(A8), Eq("a8"));
  EXPECT_THAT(ToString(H1), Eq("h1"));
  EXPECT_THAT(ToString(D5), Eq("d5"));
  EXPECT_THAT(ToString(A1), Eq("a1"));
  EXPECT_THAT(ToString(H1), Eq("h1"));
}

}  // namespace
}  // namespace chessengine
