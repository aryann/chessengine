#include "engine/game.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::IsEmpty;
using ::testing::IsFalse;
using ::testing::IsTrue;
using ::testing::Ne;
using ::testing::Not;

TEST(GetRepetitionCount, NoRepetition) {
  Game game;
  EXPECT_THAT(game.GetRepetitionCount(), Eq(0));

  game.Do(Move(E2, E4));
  EXPECT_THAT(game.GetRepetitionCount(), Eq(0));

  game.Do(Move(E7, E5));
  EXPECT_THAT(game.GetRepetitionCount(), Eq(0));

  game.Do(Move(B2, C3));
  EXPECT_THAT(game.GetRepetitionCount(), Eq(0));

  game.Do(Move(B8, C6));
  EXPECT_THAT(game.GetRepetitionCount(), Eq(0));

  game.Do(Move(C3, B2));
  EXPECT_THAT(game.GetRepetitionCount(), Eq(0));

  game.Do(Move(C6, B8));
  EXPECT_THAT(game.GetRepetitionCount(), Eq(1));

  game.Do(Move(B2, C3));
  EXPECT_THAT(game.GetRepetitionCount(), Eq(1));

  game.Do(Move(B8, C6));
  EXPECT_THAT(game.GetRepetitionCount(), Eq(1));

  game.Do(Move(C3, B2));
  EXPECT_THAT(game.GetRepetitionCount(), Eq(1));

  game.Do(Move(C6, B8));
  EXPECT_THAT(game.GetRepetitionCount(), Eq(2));
}

}  // namespace
}  // namespace chessengine
