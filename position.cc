#include "position.h"

#include "bitboard.h"

namespace chessengine {

Position::Position():
    side_to_move_(kWhite),
    en_passant_target_(std::nullopt),
    half_moves_(0),
    full_moves_(0) {
    // Pieces:
    pieces_[kWhitePawn] = rank::k2;
    pieces_[kBlackPawn] = rank::k7;
    pieces_[kKnight] = ToBitboard({B1, G1, B8, G8});
    pieces_[kBishop] = ToBitboard({C1, F1, C8, F8});
    pieces_[kQueen] = ToBitboard({D1, D8});
    pieces_[kKing] = ToBitboard({E1, E8});

    // Sides:
    sides_[kWhite] = rank::k1 | rank::k2;
    sides_[kBlack] = rank::k7 | rank::k8;
}

Position::Position(std::string_view fen_string):
    Position() {
    // TODO(aryann): IMplement this.
}

} // chessengine
