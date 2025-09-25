#include "position.h"
#include "bitboard.h"

namespace chessengine {

Position::Position():
    pawns_(rank::k2 | rank::k7),
    rooks_(square::ToBitboard({
            square::A1, square::H1, square::A8, square::H8,
    })),
    knights_(square::ToBitboard({
            square::B1, square::G1, square::B8, square::G8,
    })),
    bishops_(square::ToBitboard({
            square::C1, square::F1, square::C8, square::F8,
    })),
    queens_(square::ToBitboard({
            square::D1, square::D8,
    })),
    kings_(square::ToBitboard({
            square::E1, square::E8,
    })),
    white_pieces_(rank::k1 | rank::k2),
    black_pieces_(rank::k7 | rank::k8) {
}

Position::Position(std::string_view fen_string):
    Position() {
    // TODO(aryann): IMplement this.
}

} // chessengine
