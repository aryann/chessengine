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
        std::optional<Piece> piece = ParsePromotionPiece(input[0]);
        if (!piece) {
            return error;
        }
        return Move(*from, *to, *piece);
    }

    if (input == "#c") {
        return Move(*from, *to, kCastle);
    }

    return error;
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << ToString(move.from()) << ToString(move.to());
    if (move.IsPromotion()) {
        static char kPieceChars[] = {'n', 'b', 'r', 'q'};
        os << kPieceChars[move.GetPromotedPiece() - kKnight];
    }

    if (move.IsCastling()) {
        os << "#c";
    }
    return os;
}

} // namespace chessengine
