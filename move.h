#ifndef CHESS_ENGINE_MOVE_H_
#define CHESS_ENGINE_MOVE_H_

#include <cstdint>

#include "types.h"

namespace chessengine {

class Move {
public:
    Move(Square from, Square to):
        bits_(from + (to << 6)) {
    }

    Square from() const {
        return static_cast<Square>(bits_ & 0b111111);
    }

    Square to() const {
        return static_cast<Square>((bits_ >> 6) & 0b111111);
    }

private:
    // Stores the move state:
    //
    //   * Bits [0,  6]: The `from` Square.
    //   * Bits [7, 13]: The `to` Square.
    std::uint16_t bits_;
};

} // namespace chessengine

#endif // CHESS_ENGINE_MOVE_H_
