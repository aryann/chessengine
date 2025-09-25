#ifndef CHESS_ENGINE_POSITION_H_
#define CHESS_ENGINE_POSITION_H_

#include <string_view>

#include "bitboard.h"

namespace chessengine {

class Position {
public:
    Position();

    explicit Position(std::string_view fen_string);

private:
    Bitboard pawns_;
    Bitboard rooks_;
    Bitboard knights_;
    Bitboard bishops_;
    Bitboard queens_;
    Bitboard kings_;

    Bitboard white_pieces_;
    Bitboard black_pieces_;
};

} // namespace chessengine

#endif // CHESS_ENGINE_POSITION_H_

