#include "search/evaluation.h"

#include "engine/position.h"

namespace chessengine {
namespace {

// Piece placement value source:
// https://www.chessprogramming.org/Simplified_Evaluation_Function.

constexpr std::array<std::int8_t, kNumSquares> kWhitePawnPlacementScores = {
    0,  0,  0,   0,   0,   0,   0,  0,   //
    50, 50, 50,  50,  50,  50,  50, 50,  //
    10, 10, 20,  30,  30,  20,  10, 10,  //
    5,  5,  10,  25,  25,  10,  5,  5,   //
    0,  0,  0,   20,  20,  0,   0,  0,   //
    5,  -5, -10, 0,   0,   -10, -5, 5,   //
    5,  10, 10,  -20, -20, 10,  10, 5,   //
    0,  0,  0,   0,   0,   0,   0,  0    //
};

constexpr std::array<std::int8_t, kNumSquares> kWhiteKnightPlacementScores = {
    -50, -40, -30, -30, -30, -30, -40, -50,  //
    -40, -20, 0,   0,   0,   0,   -20, -40,  //
    -30, 0,   10,  15,  15,  10,  0,   -30,  //
    -30, 5,   15,  20,  20,  15,  5,   -30,  //
    -30, 0,   15,  20,  20,  15,  0,   -30,  //
    -30, 5,   10,  15,  15,  10,  5,   -30,  //
    -40, -20, 0,   5,   5,   0,   -20, -40,  //
    -50, -40, -30, -30, -30, -30, -40, -50,  //
};

constexpr std::array<std::int8_t, kNumSquares> kWhiteBishopPlacementScores = {
    -20, -10, -10, -10, -10, -10, -10, -20,  //
    -10, 0,   0,   0,   0,   0,   0,   -10,  //
    -10, 0,   5,   10,  10,  5,   0,   -10,  //
    -10, 5,   5,   10,  10,  5,   5,   -10,  //
    -10, 0,   10,  10,  10,  10,  0,   -10,  //
    -10, 10,  10,  10,  10,  10,  10,  -10,  //
    -10, 5,   0,   0,   0,   0,   5,   -10,  //
    -20, -10, -10, -10, -10, -10, -10, -20,  //
};

constexpr std::array<std::int8_t, kNumSquares> kWhiteRookPlacementScores = {
    0,  0,  0,  0,  0,  0,  0,  0,   //
    5,  10, 10, 10, 10, 10, 10, 5,   //
    -5, 0,  0,  0,  0,  0,  0,  -5,  //
    -5, 0,  0,  0,  0,  0,  0,  -5,  //
    -5, 0,  0,  0,  0,  0,  0,  -5,  //
    -5, 0,  0,  0,  0,  0,  0,  -5,  //
    -5, 0,  0,  0,  0,  0,  0,  -5,  //
    0,  0,  0,  5,  5,  0,  0,  0,   //
};

constexpr std::array<std::int8_t, kNumSquares> kWhiteQueenPlacementScores = {
    -20, -10, -10, -5, -5, -10, -10, -20,  //
    -10, 0,   0,   0,  0,  0,   0,   -10,  //
    -10, 0,   5,   5,  5,  5,   0,   -10,  //
    -5,  0,   5,   5,  5,  5,   0,   -5,   //
    0,   0,   5,   5,  5,  5,   0,   -5,   //
    -10, 5,   5,   5,  5,  5,   0,   -10,  //
    -10, 0,   5,   0,  0,  0,   0,   -10,  //
    -20, -10, -10, -5, -5, -10, -10, -20,  //
};

// TODO(aryann): Generate end-game placement scores.
constexpr std::array<std::int8_t, kNumSquares> kWhiteKingPlacementScores = {
    -30, -40, -40, -50, -50, -40, -40, -30,  //
    -30, -40, -40, -50, -50, -40, -40, -30,  //
    -30, -40, -40, -50, -50, -40, -40, -30,  //
    -30, -40, -40, -50, -50, -40, -40, -30,  //
    -20, -30, -30, -40, -40, -30, -30, -20,  //
    -10, -20, -20, -20, -20, -20, -20, -10,  //
    20,  20,  0,   0,   0,   0,   20,  20,   //
    20,  30,  10,  0,   0,   10,  30,  20,   //
};

constexpr std::array<std::int8_t, kNumSquares> kBlackPawnPlacementScores = {
    0,  0,  0,   0,   0,   0,   0,  0,   //
    5,  10, 10,  -20, -20, 10,  10, 5,   //
    5,  -5, -10, 0,   0,   -10, -5, 5,   //
    0,  0,  0,   20,  20,  0,   0,  0,   //
    5,  5,  10,  25,  25,  10,  5,  5,   //
    10, 10, 20,  30,  30,  20,  10, 10,  //
    50, 50, 50,  50,  50,  50,  50, 50,  //
    0,  0,  0,   0,   0,   0,   0,  0    //
};

constexpr std::array<std::int8_t, kNumSquares> kBlackKnightPlacementScores = {
    -50, -40, -30, -30, -30, -30, -40, -50,  //
    -40, -20, 0,   5,   5,   0,   -20, -40,  //
    -30, 5,   10,  15,  15,  10,  5,   -30,  //
    -30, 0,   15,  20,  20,  15,  0,   -30,  //
    -30, 5,   15,  20,  20,  15,  5,   -30,  //
    -30, 0,   10,  15,  15,  10,  0,   -30,  //
    -40, -20, 0,   0,   0,   0,   -20, -40,  //
    -50, -40, -30, -30, -30, -30, -40, -50,  //
};

constexpr std::array<std::int8_t, kNumSquares> kBlackBishopPlacementScores = {
    -20, -10, -10, -10, -10, -10, -10, -20,  //
    -10, 5,   0,   0,   0,   0,   5,   -10,  //
    -10, 10,  10,  10,  10,  10,  10,  -10,  //
    -10, 0,   10,  10,  10,  10,  0,   -10,  //
    -10, 5,   5,   10,  10,  5,   5,   -10,  //
    -10, 0,   5,   10,  10,  5,   0,   -10,  //
    -10, 0,   0,   0,   0,   0,   0,   -10,  //
    -20, -10, -10, -10, -10, -10, -10, -20,  //
};

constexpr std::array<std::int8_t, kNumSquares> kBlackRookPlacementScores = {
    0,  0,  0,  5,  5,  0,  0,  0,   //
    -5, 0,  0,  0,  0,  0,  0,  -5,  //
    -5, 0,  0,  0,  0,  0,  0,  -5,  //
    -5, 0,  0,  0,  0,  0,  0,  -5,  //
    -5, 0,  0,  0,  0,  0,  0,  -5,  //
    -5, 0,  0,  0,  0,  0,  0,  -5,  //
    5,  10, 10, 10, 10, 10, 10, 5,   //
    0,  0,  0,  0,  0,  0,  0,  0,   //
};

constexpr std::array<std::int8_t, kNumSquares> kBlackQueenPlacementScores = {
    -20, -10, -10, -5, -5, -10, -10, -20,  //
    -10, 0,   5,   0,  0,  0,   0,   -10,  //
    -10, 5,   5,   5,  5,  5,   0,   -10,  //
    0,   0,   5,   5,  5,  5,   0,   -5,   //
    -5,  0,   5,   5,  5,  5,   0,   -5,   //
    -10, 0,   5,   5,  5,  5,   0,   -10,  //
    -10, 0,   0,   0,  0,  0,   0,   -10,  //
    -20, -10, -10, -5, -5, -10, -10, -20,  //
};

constexpr std::array<std::int8_t, kNumSquares> kBlackKingPlacementScores = {
    20,  30,  10,  0,   0,   10,  30,  20,   //
    20,  20,  0,   0,   0,   0,   20,  20,   //
    -10, -20, -20, -20, -20, -20, -20, -10,  //
    -20, -30, -30, -40, -40, -30, -30, -20,  //
    -30, -40, -40, -50, -50, -40, -40, -30,  //
    -30, -40, -40, -50, -50, -40, -40, -30,  //
    -30, -40, -40, -50, -50, -40, -40, -30,  //
    -30, -40, -40, -50, -50, -40, -40, -30,  //
};

[[nodiscard]] constexpr int GetPlacementScore(
    const std::array<std::int8_t, kNumSquares>& scores, Bitboard pieces) {
  int score = 0;
  while (pieces) {
    Square square = pieces.PopLeastSignificantBit();
    score += scores[square];
  }
  return score;
}

[[nodiscard]] int GetWhitePlacementScore(const Position& position) {
  int pawns = GetPlacementScore(kWhitePawnPlacementScores,
                                position.GetPieces(kWhite, kPawn));
  int knights = GetPlacementScore(kWhiteKnightPlacementScores,
                                  position.GetPieces(kWhite, kKnight));
  int bishops = GetPlacementScore(kWhiteBishopPlacementScores,
                                  position.GetPieces(kWhite, kBishop));
  int rooks = GetPlacementScore(kWhiteRookPlacementScores,
                                position.GetPieces(kWhite, kRook));
  int queen = GetPlacementScore(kWhiteQueenPlacementScores,
                                position.GetPieces(kWhite, kQueen));
  int king = GetPlacementScore(kWhiteKingPlacementScores,
                               position.GetPieces(kWhite, kKing));

  return pawns + knights + bishops + rooks + queen + king;
}

[[nodiscard]] int GetBlackPlacementScore(const Position& position) {
  int pawns = GetPlacementScore(kBlackPawnPlacementScores,
                                position.GetPieces(kBlack, kPawn));
  int knights = GetPlacementScore(kBlackKnightPlacementScores,
                                  position.GetPieces(kBlack, kKnight));
  int bishops = GetPlacementScore(kBlackBishopPlacementScores,
                                  position.GetPieces(kBlack, kBishop));
  int rooks = GetPlacementScore(kBlackRookPlacementScores,
                                position.GetPieces(kBlack, kRook));
  int queen = GetPlacementScore(kBlackQueenPlacementScores,
                                position.GetPieces(kBlack, kQueen));
  int king = GetPlacementScore(kBlackKingPlacementScores,
                               position.GetPieces(kBlack, kKing));

  return pawns + knights + bishops + rooks + queen + king;
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
  return GetWhitePlacementScore(position) - GetBlackPlacementScore(position);
}

[[nodiscard]] int Evaluate(const Position& position) {
  int score = GetMaterialScore(position) + GetPlacementScore(position);
  if (position.SideToMove() == kBlack) {
    return -score;
  }
  return score;
}

}  // namespace chessengine
