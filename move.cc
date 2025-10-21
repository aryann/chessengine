#include "move.h"

#include <ostream>

namespace chessengine {
namespace {

std::optional<Piece> ParsePromotionPiece(char c) {
    switch (c) {
        case 'n':
            return kKnight;
        case 'b':
            return kBishop;
        case 'r':
            return kRook;
        case 'q':
            return kQueen;
        default:
            return std::nullopt;
    }
}

} // namespace

std::expected<Move, std::string> Move::FromUCI(std::string_view input) {
    if (input.size() < 4 || input.size() > 5) {
        return std::unexpected(std::format("Invalid UCI move: {}", input));
    }

    std::optional<Square> from = ParseSquare(input.substr(0, 2));
    std::optional<Square> to = ParseSquare(input.substr(2, 2));
    if (!from || !to) {
        return std::unexpected(std::format("Invalid UCI move: {}", input));
    }

    if (input.size() == 5) {
        std::optional<Piece> piece = ParsePromotionPiece(input[4]);
        if (!piece) {
            return std::unexpected(std::format("Invalid UCI move: {}", input));
        }
        return Move(*from, *to, *piece);
    }

    return Move(*from, *to);
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << ToString(move.from()) << ToString(move.to());
    if (move.IsPromotion()) {
        static char kPieceChars[] = {'n', 'b', 'r', 'q'};
        os << kPieceChars[move.GetPromotedPiece() - kKnight];
    }
    return os;
}

} // namespace chessengine
