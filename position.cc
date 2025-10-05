#include "position.h"

#include "bitboard.h"
#include "absl/strings/str_split.h"

namespace chessengine {

Position Position::Make() {
    Position position;

    // Pieces:
    position.pieces_[kWhitePawn] = rank::k2;
    position.pieces_[kBlackPawn] = rank::k7;
    position.pieces_[kKnight] = {B1, G1, B8, G8};
    position.pieces_[kBishop] = {C1, F1, C8, F8};
    position.pieces_[kRook] = {A1, H1, A8, H8};
    position.pieces_[kQueen] = {D1, D8};
    position.pieces_[kKing] = {E1, E8};

    // Sides:
    position.sides_[kWhite] = rank::k1 | rank::k2;
    position.sides_[kBlack] = rank::k7 | rank::k8;

    return position;
}

[[nodiscard]] Piece Position::piece(Square square) const {
    if (pieces_[kBlackPawn] & square) {
        return kBlackPawn;
    }
    if (pieces_[kWhitePawn] & square) {
        return kWhitePawn;
    }
    if (pieces_[kKnight] & square) {
        return kKnight;
    }
    if (pieces_[kBishop] & square) {
        return kBishop;
    }
    if (pieces_[kRook] & square) {
        return kRook;
    }
    if (pieces_[kQueen] & square) {
        return kQueen;
    }
    if (pieces_[kKing] & square) {
        return kKing;
    }

    return kEmptyPiece;
}

[[nodiscard]] Side Position::side(Square square) const {
    if (sides_[kWhite] & square) {
        return kWhite;
    }
    if (sides_[kBlack] & square) {
        return kBlack;
    }
    return kEmptySide;
}

[[nodiscard]] Bitboard Position::Pieces() const {
    return sides_[kWhite] | sides_[kBlack];
}

[[nodiscard]] Bitboard Position::Pieces(Side side) const {
    return sides_[side];
}

[[nodiscard]] Bitboard Position::Pieces(Side side, Piece type) const {
    return sides_[side] & pieces_[type];
}

namespace {

std::expected<void, std::string> FillPiece(char curr, Square square, std::array<Bitboard, kNumPieces> &pieces) {
    if (curr == 'p') {
        pieces[kBlackPawn].Set(square);
    } else if (curr == 'P') {
        pieces[kWhitePawn].Set(square);
    } else if (curr == 'n' || curr == 'N') {
        pieces[kKnight].Set(square);
    } else if (curr == 'b' || curr == 'B') {
        pieces[kBishop].Set(square);
    } else if (curr == 'r' || curr == 'R') {
        pieces[kRook].Set(square);
    } else if (curr == 'q' || curr == 'Q') {
        pieces[kQueen].Set(square);
    } else if (curr == 'k' || curr == 'K') {
        pieces[kKing].Set(square);
    } else {
        return std::unexpected(std::format("FEN string contained invalid square character: {}", curr));
    }

    return {};
}

std::expected<void, std::string> ParseBoard(std::string_view board,
                                            std::array<Bitboard, kNumPieces> &pieces,
                                            std::array<Bitboard, kNumSides> &sides) {
    int square_index = 0;
    for (char curr: board) {
        if (square_index > 63) {
            return std::unexpected("FEN string did not contain exactly 64 squares.");
        }

        if (curr == '/') {
            continue;
        }

        if (std::isdigit(curr)) {
            int empty_squares = curr - '0';
            square_index += empty_squares;
            continue;
        }

        auto square = static_cast<Square>(square_index);

        Side side = std::isupper(curr) ? kWhite : kBlack;
        sides[side].Set(square);

        if (auto result = FillPiece(curr, square, pieces); !result.has_value()) {
            return result;
        }

        ++square_index;
    }

    return {};
}

} // namespace

std::expected<Position, std::string> Position::Make(std::string_view fen) {
    std::vector<std::string_view> parts = absl::StrSplit(fen, absl::ByAsciiWhitespace());
    if (parts.size() != 6) {
        return std::unexpected(std::format("FEN string must have 6 parts; received: {}", parts.size()));
    }

    std::string_view board = parts[0];
    std::string_view side_to_move = parts[1];
    std::string_view castling_rights = parts[2];
    std::string_view en_passant_target = parts[3];
    std::string_view half_moves = parts[4];
    std::string_view full_moves = parts[5];

    Position position;
    if (auto result = ParseBoard(board, position.pieces_, position.sides_); !result.has_value()) {
        return std::unexpected(result.error());
    }

    if (side_to_move == "w") {
        position.side_to_move_ = kWhite;
    } else if (side_to_move == "b") {
        position.side_to_move_ = kBlack;
    } else {
        return std::unexpected(std::format("Invalid side to move value: {}", side_to_move));
    }

    return position;
}

} // chessengine
