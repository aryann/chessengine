#include "search/evaluation.h"

#include "engine/position.h"

namespace follychess {
namespace {

// Piece placement value source:
// https://www.chessprogramming.org/Simplified_Evaluation_Function.
//
// All placement values are from white's perspective.
consteval auto MakePlacementScores() {
  std::array<std::array<std::int8_t, kNumSquares>, kNumPieces> result = {};

  result[kPawn] = {
      0,  0,  0,   0,   0,   0,   0,  0,   //
      50, 50, 50,  50,  50,  50,  50, 50,  //
      10, 10, 20,  30,  30,  20,  10, 10,  //
      5,  5,  10,  25,  25,  10,  5,  5,   //
      0,  0,  0,   20,  20,  0,   0,  0,   //
      5,  -5, -10, 0,   0,   -10, -5, 5,   //
      5,  10, 10,  -20, -20, 10,  10, 5,   //
      0,  0,  0,   0,   0,   0,   0,  0    //
  };

  result[kKnight] = {
      -50, -40, -30, -30, -30, -30, -40, -50,  //
      -40, -20, 0,   0,   0,   0,   -20, -40,  //
      -30, 0,   10,  15,  15,  10,  0,   -30,  //
      -30, 5,   15,  20,  20,  15,  5,   -30,  //
      -30, 0,   15,  20,  20,  15,  0,   -30,  //
      -30, 5,   10,  15,  15,  10,  5,   -30,  //
      -40, -20, 0,   5,   5,   0,   -20, -40,  //
      -50, -40, -30, -30, -30, -30, -40, -50,  //
  };

  result[kBishop] = {
      -20, -10, -10, -10, -10, -10, -10, -20,  //
      -10, 0,   0,   0,   0,   0,   0,   -10,  //
      -10, 0,   5,   10,  10,  5,   0,   -10,  //
      -10, 5,   5,   10,  10,  5,   5,   -10,  //
      -10, 0,   10,  10,  10,  10,  0,   -10,  //
      -10, 10,  10,  10,  10,  10,  10,  -10,  //
      -10, 5,   0,   0,   0,   0,   5,   -10,  //
      -20, -10, -10, -10, -10, -10, -10, -20,  //
  };

  result[kRook] = {
      0,  0,  0,  0,  0,  0,  0,  0,   //
      5,  10, 10, 10, 10, 10, 10, 5,   //
      -5, 0,  0,  0,  0,  0,  0,  -5,  //
      -5, 0,  0,  0,  0,  0,  0,  -5,  //
      -5, 0,  0,  0,  0,  0,  0,  -5,  //
      -5, 0,  0,  0,  0,  0,  0,  -5,  //
      -5, 0,  0,  0,  0,  0,  0,  -5,  //
      0,  0,  0,  5,  5,  0,  0,  0,   //
  };

  result[kQueen] = {
      -20, -10, -10, -5, -5, -10, -10, -20,  //
      -10, 0,   0,   0,  0,  0,   0,   -10,  //
      -10, 0,   5,   5,  5,  5,   0,   -10,  //
      -5,  0,   5,   5,  5,  5,   0,   -5,   //
      0,   0,   5,   5,  5,  5,   0,   -5,   //
      -10, 5,   5,   5,  5,  5,   0,   -10,  //
      -10, 0,   5,   0,  0,  0,   0,   -10,  //
      -20, -10, -10, -5, -5, -10, -10, -20,  //
  };

  result[kKing] = {
      // TODO(aryann): Generate end-game placement scores.
      -30, -40, -40, -50, -50, -40, -40, -30,  //
      -30, -40, -40, -50, -50, -40, -40, -30,  //
      -30, -40, -40, -50, -50, -40, -40, -30,  //
      -30, -40, -40, -50, -50, -40, -40, -30,  //
      -20, -30, -30, -40, -40, -30, -30, -20,  //
      -10, -20, -20, -20, -20, -20, -20, -10,  //
      20,  20,  0,   0,   0,   0,   20,  20,   //
      20,  30,  10,  0,   0,   10,  30,  20,   //
  };

  return result;
}

constexpr auto kPlacementScores = MakePlacementScores();

template <Side Side, Piece Piece>
[[nodiscard]] constexpr int GetPlacementScore(const Position& position) {
  Bitboard pieces = position.GetPieces(Side, Piece);
  const std::array<std::int8_t, kNumSquares>& scores = kPlacementScores[Piece];

  int score = 0;
  while (pieces) {
    Square square = pieces.PopLeastSignificantBit();
    if constexpr (Side == kBlack) {
      square = Reflect(square);
    }

    score += scores[square];
  }
  return score;
}

template <Side Side>
[[nodiscard]] int GetPlacementScore(const Position& position) {
  return GetPlacementScore<Side, kPawn>(position) +
         GetPlacementScore<Side, kKnight>(position) +
         GetPlacementScore<Side, kBishop>(position) +
         GetPlacementScore<Side, kRook>(position) +
         GetPlacementScore<Side, kQueen>(position) +
         GetPlacementScore<Side, kKing>(position);
}

[[nodiscard]] constexpr int SideDifference(const Position& position,
                                           const Piece piece) {
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

[[nodiscard]] int GetPlacementScore(const Position& position) {
  return GetPlacementScore<kWhite>(position) -
         GetPlacementScore<kBlack>(position);
}

[[nodiscard]] int Evaluate(const Position& position) {
  return GetMaterialScore(position) + GetPlacementScore(position);
}

}  // namespace follychess
