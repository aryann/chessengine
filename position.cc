#include "position.h"

#include "bitboard.h"

namespace chessengine {

Position::Position():
    pawns_(rank::k2 | rank::k7),
    rooks_(ToBitboard({A1, H1, A8, H8})),
    knights_(ToBitboard({B1, G1, B8, G8})),
    bishops_(ToBitboard({C1, F1, C8, F8})),
    queens_(ToBitboard({D1, D8})),
    kings_(ToBitboard({E1, E8})),
    white_pieces_(rank::k1 | rank::k2),
    black_pieces_(rank::k7 | rank::k8),
    side_to_move_(kWhite),
    en_passant_target_(std::nullopt),
    half_moves_(0),
    full_moves_(0) {
}

Position::Position(std::string_view fen_string):
    Position() {
    // TODO(aryann): IMplement this.
}

} // chessengine
