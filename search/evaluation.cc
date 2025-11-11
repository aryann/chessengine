#include "search/evaluation.h"

#include "engine/position.h"

namespace chessengine {

namespace {
[[nodiscard]] int SideDifference(const Position& position, const Piece piece) {
  return position.GetPieces(kWhite, piece).GetCount() -
         position.GetPieces(kBlack, piece).GetCount();
}

}  // namespace

[[nodiscard]] int GetMaterialScore(const Position& position) {
  return 20'000 * SideDifference(position, kKing) +
         900 * SideDifference(position, kQueen) +
         500 * SideDifference(position, kRook) +
         300 * SideDifference(position, kBishop) +
         300 * SideDifference(position, kKnight) +
         100 * SideDifference(position, kPawn);
}

}  // namespace chessengine
