#ifndef CHESS_ENGINE_MOVE_H_
#define CHESS_ENGINE_MOVE_H_

#include <cstdint>
#include <iostream>

#include "types.h"

namespace chessengine {

class Move {
public:
    constexpr Move(Square from, Square to):
        bits_(from + (to << 6)) {
    }

    constexpr Square from() const {
        return static_cast<Square>(bits_ & 0b111111);
    }

    constexpr Square to() const {
        return static_cast<Square>((bits_ >> 6) & 0b111111);
    }

    constexpr bool operator==(const Move &other) const = default;

private:
    // Stores the move state:
    //
    //   * Bits [0,  6]: The `from` Square.
    //   * Bits [7, 13]: The `to` Square.
    std::uint16_t bits_;
};

std::ostream &operator<<(std::ostream &os, const Move &move);

} // namespace chessengine

#endif // CHESS_ENGINE_MOVE_H_
