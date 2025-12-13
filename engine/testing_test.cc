#include "engine/testing.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "engine/testing.h"

namespace follychess {
namespace {

using ::testing::Eq;
using ::testing::IsTrue;
using ::testing::Optional;

TEST(TryMakePosition, Ok) {
  EXPECT_THAT(TryMakePosition("8: r n b q k b n r\n"
                              "7: p p p p p p p p\n"
                              "6: . . . . . . . .\n"
                              "5: . . . . . . . .\n"
                              "4: . . . . . . . .\n"
                              "3: . . . . . . . .\n"
                              "2: P P P P P P P P\n"
                              "1: R N B Q K B N R\n"
                              "   a b c d e f g h\n"
                              "\n"
                              "   w KQkq - 0 1\n")
                  .has_value(),
              IsTrue());

  EXPECT_THAT(TryMakePosition("8: r . . . k . . r"
                              "7: p . p p q p b ."
                              "6: b n . . p n p ."
                              "5: . . . P N . . ."
                              "4: . p . . P . . ."
                              "3: . . N . . Q . p"
                              "2: P P P B B P P P"
                              "1: R . . . K . . R"
                              "   a b c d e f g h"
                              ""
                              "   w KQkq - 0 1")
                  .has_value(),
              IsTrue());

  EXPECT_THAT(TryMakePosition("8: . . . . . . . ."
                              "7: . . p . . . . ."
                              "6: . . . p . . . ."
                              "5: K P . . . . . r"
                              "4: . R . . . p . k"
                              "3: . . . . . . . ."
                              "2: . . . . P . P ."
                              "1: . . . . . . . ."
                              "   a b c d e f g h"
                              //
                              "   w - a3 0 1")
                  .has_value(),
              IsTrue());
}

TEST(MakePosition, Failures) {
  ASSERT_DEATH(MakePosition(""), "Invalid position input: ");
  ASSERT_DEATH(MakePosition("KQkq"), "Invalid position input: KQkq");
}

}  // namespace
}  // namespace follychess
