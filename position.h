#ifndef CHESS_ENGINE_POSITION_H_
#define CHESS_ENGINE_POSITION_H_

#include <string_view>

#include "bitboard.h"
#include "types.h"

namespace chessengine {

class Position {
public:
    Position();

    explicit Position(std::string_view fen_string);

private:
    std::array<Bitboard, kNumPieces> pieces_;
    std::array<Bitboard, kNumSides> sides_;

    Side side_to_move_;
    std::optional<Square> en_passant_target_;

    // TODO(aryann): Add castling rights.

    int half_moves_;
    int full_moves_;
};

} // namespace chessengine

#endif // CHESS_ENGINE_POSITION_H_

