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
  return 200 * SideDifference(position, kKing) +
         9 * SideDifference(position, kQueen) +
         5 * SideDifference(position, kRook) +
         3 * SideDifference(position, kBishop) +
         3 * SideDifference(position, kKnight) +
         1 * SideDifference(position, kPawn);
}

}  // namespace chessengine
