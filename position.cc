#include "position.h"

#include "absl/strings/str_cat.h"

#include "attacks.h"
#include "absl/log/check.h"
#include "absl/strings/str_split.h"
#include "bitboard.h"
#include "castling_rights.h"

namespace chessengine {

Piece Position::GetPiece(Square square) const {
    if (pieces_[kPawn] & square) {
        return kPawn;
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

Side Position::GetSide(Square square) const {
    if (sides_[kWhite] & square) {
        return kWhite;
    }
    if (sides_[kBlack] & square) {
        return kBlack;
    }
    return kEmptySide;
}

Bitboard Position::GetPieces() const {
    return sides_[kWhite] | sides_[kBlack];
}

Bitboard Position::GetPieces(Side side) const {
    return sides_[side];
}

Bitboard Position::GetPieces(Piece type) const {
    return pieces_[type];
}

Bitboard Position::GetPieces(Side side, Piece type) const {
    return sides_[side] & pieces_[type];
}

Bitboard Position::GetAttackers(Square to) const {
    Bitboard occupied = GetPieces();
    Bitboard attackers;

    attackers |= GetPawnAttacks(to, SideToMove()) & GetPieces(kPawn);
    attackers |= GenerateAttacks<kKnight>(to, occupied) & GetPieces(kKnight);
    attackers |= GenerateAttacks<kKing>(to, occupied) & GetPieces(kKing);

    // Generates attacks from rooks, bishops, and queens:
    attackers |= GenerateAttacks<kRook>(to, occupied) &
            (GetPieces(kRook) | GetPieces(kQueen));
    attackers |= GenerateAttacks<kBishop>(to, occupied) &
            (GetPieces(kBishop) | GetPieces(kQueen));

    return attackers;
}

Square Position::GetKing() const {
    Bitboard king = GetPieces(SideToMove(), kKing);
    DCHECK(king && !king.HasMoreThanOneBit())
        << "Board must have exactly one king of each color.\n\n"
        << std::format("{}", *this);

    return king.LeastSignificantBit();
}

Bitboard Position::GetCheckers() const {
    return GetAttackers(GetKing()) & GetPieces(~SideToMove());
}

namespace {

std::expected<void, std::string> FillPiece(char curr, Square square, std::array<Bitboard, kNumPieces> &pieces) {
    if (curr == 'p' || curr == 'P') {
        pieces[kPawn].Set(square);
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

std::expected<void, std::string> SetCastlingRights(std::string_view input, CastlingRights &rights) {
    if (input == "-") {
        return {};
    }

    if (input.find_first_not_of("KQkq") != std::string::npos) {
        return std::unexpected(std::format("Invalid castling rights: {}", input));
    }

    if (input.contains("K")) {
        rights.SetKingSide(kWhite);
    }
    if (input.contains("k")) {
        rights.SetKingSide(kBlack);
    }
    if (input.contains("Q")) {
        rights.SetQueenSide(kWhite);
    }
    if (input.contains("q")) {
        rights.SetQueenSide(kBlack);
    }

    return {};
}

bool IsNumeric(std::string_view input) {
    return std::ranges::all_of(input, isdigit);
}

} // namespace

Position Position::Starting() {
    constexpr absl::string_view kFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    std::expected<Position, std::string> result = FromFen(kFen);
    CHECK(result.has_value()) << "Failed for parse starting position FEN: " << result.error();
    return result.value();
}

std::expected<Position, std::string> Position::FromFen(std::string_view fen) {
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

    if (auto result = SetCastlingRights(castling_rights, position.castling_rights_); !result.has_value()) {
        return std::unexpected(result.error());
    }

    if (en_passant_target != "-") {
        position.en_passant_target_ = ParseSquare(en_passant_target);
        if (!position.en_passant_target_) {
            return std::unexpected(std::format("Invalid en-passant target: {}", en_passant_target));
        }
    }

    if (!IsNumeric(half_moves)) {
        return std::unexpected(std::format("Invalid half moves: {}", half_moves));
    }
    position.half_moves_ = std::stoi(std::string(half_moves));

    if (!IsNumeric(full_moves)) {
        return std::unexpected(std::format("Invalid full moves: {}", full_moves));
    }
    position.full_moves_ = std::stoi(std::string(full_moves));

    return position;
}

void Position::Do(const Move &move) {
    // TODO(aryann): Reset the half move clock if there was a pawn move.
    ++half_moves_;
    if (side_to_move_ == kBlack) {
        ++full_moves_;
    }

    if (move.GetCapturedPiece() != kEmptyPiece) {
        half_moves_ = 0;
        pieces_[move.GetCapturedPiece()].Clear(move.to());

        Side side = GetSide(move.to());
        DCHECK(side != kEmptySide);
        sides_[side].Clear(move.to());
    }

    // TODO(aryann): Consider replacing this with:
    //
    //   Bitboard from_to = move.from() | move.to();
    //   pieces_[piece] ^= from_to;
    //
    Piece piece = GetPiece(move.from());
    DCHECK(piece != kEmptyPiece);

    pieces_[piece].Clear(move.from());
    pieces_[piece].Set(move.to());

    Side side = GetSide(move.from());
    DCHECK(side != kEmptySide);

    sides_[side].Clear(move.from());
    sides_[side].Set(move.to());

    side_to_move_ = ~side_to_move_;
}

void Position::Undo(const Move &move) {
    Piece piece = GetPiece(move.to());
    DCHECK(piece != kEmptyPiece);

    pieces_[piece].Clear(move.to());
    pieces_[piece].Set(move.from());

    Side side = GetSide(move.to());
    DCHECK(side != kEmptySide);

    sides_[side].Clear(move.to());
    sides_[side].Set(move.from());

    if (move.GetCapturedPiece() == kEmptyPiece) {
        --half_moves_;
    } else {
        // Restores a captured piece.
        half_moves_ = move.GetPreviousHalfMoves();
        pieces_[move.GetCapturedPiece()].Set(move.to());
        sides_[~side].Set(move.to());
    }

    if (side == kBlack) {
        --full_moves_;
    }
    side_to_move_ = ~side_to_move_;
}

} // chessengine
