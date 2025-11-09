#include "engine/zobrist.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::Not;

TEST(ZobristHash, Empty) {
  EXPECT_THAT(ZobristHash().GetHash(), Eq(0ULL));
  EXPECT_THAT(ZobristHash(), Eq(ZobristHash()));
}

TEST(ZobristHash, PieceMoves) {
  ZobristHash hash;
  std::uint64_t v0 = hash.GetHash();
  EXPECT_THAT(v0, Eq(0ULL));

  // Simulate e2e4 in the starting position:
  hash.Update(E2, kPawn, kWhite);
  hash.Update(E4, kPawn, kWhite);

  std::uint64_t v1 = hash.GetHash();
  EXPECT_THAT(v1, Not(Eq(v0)));

  // Undo part of e2e4:
  hash.Update(E2, kPawn, kWhite);
  EXPECT_THAT(hash.GetHash(), Not(Eq(v1)));

  // Fully undo e2e4:
  hash.Update(E4, kPawn, kWhite);
  EXPECT_THAT(hash.GetHash(), Eq(v0));

  // Make e2e4 again:
  hash.Update(E2, kPawn, kWhite);
  hash.Update(E4, kPawn, kWhite);
  EXPECT_THAT(hash.GetHash(), Eq(v1));
}

TEST(ZobristHash, SideToMove) {
  ZobristHash hash;
  hash.Update(E7, kPawn, kBlack);
  hash.Update(E5, kPawn, kBlack);

  std::uint64_t v0 = hash.GetHash();
  hash.UpdateSideToMove();
  std::uint64_t v1 = hash.GetHash();
  hash.UpdateSideToMove();
  std::uint64_t v2 = hash.GetHash();
  hash.UpdateSideToMove();
  std::uint64_t v3 = hash.GetHash();
  hash.UpdateSideToMove();
  std::uint64_t v4 = hash.GetHash();

  EXPECT_THAT(v0, Not(Eq(v1)));
  EXPECT_THAT(v0, Eq(v2));
  EXPECT_THAT(v0, Not(Eq(v3)));
  EXPECT_THAT(v0, Eq(v4));
}

TEST(ZobristHash, EnPassant) {
  ZobristHash hash;
  hash.Update(E7, kPawn, kBlack);
  hash.Update(E5, kPawn, kBlack);

  std::uint64_t v0 = hash.GetHash();
  hash.ToggleEnPassantTarget(G3);
  std::uint64_t v1 = hash.GetHash();
  hash.ToggleEnPassantTarget(G3);
  std::uint64_t v2 = hash.GetHash();

  EXPECT_THAT(v0, Not(Eq(v1)));
  EXPECT_THAT(v0, Eq(v2));
}

}  // namespace
}  // namespace chessengine
