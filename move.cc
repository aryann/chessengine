#include "move.h"

#include <ostream>

namespace chessengine {
namespace {

std::optional<Move::Flags> ParsePromotionPiece(char c) {
  switch (c) {
    case 'n':
      return Move::Flags::kKnightPromotion;
    case 'b':
      return Move::Flags::kBishopPromotion;
    case 'r':
      return Move::Flags::kRookPromotion;
    case 'q':
      return Move::Flags::kQueenPromotion;
    default:
      return std::nullopt;
  }
}

}  // namespace

std::expected<Move, std::string> Move::FromUCI(std::string_view input) {
  auto error = std::unexpected(std::format("Invalid UCI move: {}", input));

  if (input.size() < 4) {
    return error;
  }

  std::optional<Square> from = ParseSquare(input.substr(0, 2));
  std::optional<Square> to = ParseSquare(input.substr(2, 2));
  if (!from || !to) {
    return error;
  }
  input = input.substr(4, input.size());
  if (input.empty()) {
    return Move(*from, *to);
  }

  if (input.front() != '#') {
    std::optional<Flags> promotion_piece = ParsePromotionPiece(input[0]);
    if (!promotion_piece) {
      return error;
    }

    return Move(*from, *to, *promotion_piece);
  }

  if (input == "#dpp") {
    return Move(*from, *to, kDoublePawnPush);
  }

  if (input == "#ep") {
    return Move(*from, *to, kDoublePawnPush);
  }

  if (input == "#oo") {
    return Move(*from, *to, kKingCastle);
  }

  if (input == "#ooo") {
    return Move(*from, *to, kQueenCastle);
  }

  return error;
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
  static bool kFull = true;
  move.FormatTo(std::ostream_iterator<char>(os), kFull);
  return os;
}

}  // namespace chessengine
