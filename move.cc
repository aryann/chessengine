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

} // namespaceq

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

    if (input == "#oo") {
        return Move(*from, *to, kKingCastle);
    }

    if (input == "#ooo") {
        return Move(*from, *to, kQueenCastle);
    }

    return error;
}

template<typename Out>
Out Move::FormatTo(Out out) const {
    out = std::format_to(out, "{}{}", ToString(from()), ToString(to()));

    if (IsPromotion()) {
        static char kPieceChars[] = {'n', 'b', 'r', 'q'};
        out = std::format_to(out, "{}", kPieceChars[GetPromotedPiece() - kKnight]);
    }

    if (IsKingSideCastling()) {
        out = std::format_to(out, "#oo");
    }

    if (IsQueenSideCastling()) {
        out = std::format_to(out, "#ooo");
    }

    return out;
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
    move.FormatTo(std::ostream_iterator<char>(os));
    return os;
}

} // namespace chessengine
