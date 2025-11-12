#include "move.h"

#include <ostream>

#include "absl/strings/str_split.h"

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

std::optional<Move::Flags> ParseFlags(std::string_view input) {
  std::uint8_t flags = 0;

  for (std::string_view part : absl::StrSplit(input, ';')) {
    if (part == "c") {
      flags |= Move::Flags::kCapture;
    } else if (part == "dpp") {
      flags |= Move::Flags::kDoublePawnPush;
    } else if (part == "ep") {
      flags |= Move::Flags::kEnPassantCapture;
    } else if (part == "oo") {
      flags |= Move::Flags::kKingCastle;
    } else if (part == "ooo") {
      flags |= Move::Flags::kQueenCastle;
    } else {
      return std::nullopt;
    }
  }

  return static_cast<Move::Flags>(flags);
}

}  // namespace

std::expected<Move, std::string> Move::FromUCI(std::string_view input) {
  auto error = std::unexpected(std::format("Invalid UCI move: {}", input));
  std::vector<std::string_view> parts = absl::StrSplit(input, '#');
  if (parts.size() > 2) {
    return error;
  }
  std::string_view head = parts[0];

  if (head.size() < 4) {
    return error;
  }
  if (head.size() > 5) {
    return error;
  }

  std::optional<Square> from = ParseSquare(head.substr(0, 2));
  std::optional<Square> to = ParseSquare(head.substr(2, 2));
  if (!from || !to) {
    return error;
  }

  Flags flags = kNone;
  if (parts.size() == 2) {
    std::optional<Flags> parsed = ParseFlags(parts.back());
    if (!parsed) {
      return error;
    }
    flags = *parsed;
  }

  if (head.size() == 5) {
    std::optional<Flags> promotion_flag = ParsePromotionPiece(head[4]);
    if (!promotion_flag) {
      return error;
    }
    flags = static_cast<Flags>(flags | *promotion_flag);
  }

  return Move(*from, *to, flags);
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
  static bool kFull = true;
  move.FormatTo(std::ostream_iterator<char>(os), kFull);
  return os;
}

}  // namespace chessengine
