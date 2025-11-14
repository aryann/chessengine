#include "search/move_ordering.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "engine/position.h"
#include "engine/testing.h"

namespace chessengine {
namespace {

using ::testing::ElementsAreArray;

TEST(MoveOrdering, All) {
  Position position = MakePosition(
      "8: . . . . . . . ."
      "7: . . . . . . . ."
      "6: . . p . . . . ."
      "5: . . . Q . . . ."
      "4: . . . . . . . ."
      "3: p . . . . p . ."
      "2: . P . . R . . ."
      "1: . . . . . . . ."
      "   a b c d e f g h"
      //
      "   b KQkq - 0 1");

  std::vector<Move> moves = MakeMoves({
      "a3a2",
      "a3b2#c",
      "f3e2#c",
      "f3f2",
      "c6d5#c",
      "c6c5",
  });

  OrderMoves(position, moves);
  EXPECT_THAT(moves, ElementsAreArray(MakeMoves({
                         "c6d5#c",  // Queen capture
                         "f3e2#c",  // Rook capture
                         "a3b2#c",  // Pawn capture
                         "a3a2",
                         "f3f2",
                         "c6c5",
                     })));
}

}  // namespace
}  // namespace chessengine
