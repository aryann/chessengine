#ifndef CHESS_ENGINE_MOVE_H_
#define CHESS_ENGINE_MOVE_H_

#include <cstdint>
#include <iostream>

#include "types.h"

namespace chessengine {

class MoveOptions {
public:
    MoveOptions &SetCaptured(Piece piece, std::uint8_t previous_half_moves) {
        captured_ = piece;
        previous_half_moves_ = previous_half_moves;
        return *this;
    }

    MoveOptions &SetPromoted(Piece piece) {
        promoted_ = piece;
        return *this;
    }

private:
    friend class Move;

    Piece captured_{kEmptyPiece};
    Piece promoted_{kEmptyPiece};
    std::uint8_t previous_half_moves_{0};
};

class Move {
public:
    constexpr Move(Square from, Square to, const MoveOptions &options = MoveOptions()):
        bits_(
                from +
                (to << 6) +
                (options.captured_ << 13) +
                (options.previous_half_moves_ << 20) +
                (options.promoted_ << 28)) {
    }

    [[nodiscard]] constexpr Square from() const {
        return static_cast<Square>(bits_ & 0b111111);
    }

    [[nodiscard]] constexpr Square to() const {
        return static_cast<Square>((bits_ >> 6) & 0b111111);
    }

    [[nodiscard]] constexpr Piece GetCapturedPiece() const {
        return static_cast<Piece>((bits_ >> 13) & 0b111111);
    }

    [[nodiscard]] constexpr std::uint8_t GetPreviousHalfMoves() const {
        return (bits_ >> 20) & 0b111111;
    }

    [[nodiscard]] constexpr std::uint8_t GetPromotedPiece() const {
        return static_cast<std::uint8_t>((bits_ >> 28) & 0b111111);
    }

    constexpr auto operator<=>(const Move &other) const = default;

private:
    // Stores the move state:
    //
    //   * Bits [0,   6]: The `from` Square.
    //   * Bits [7,  13]: The `to` Square.
    //   * Bits [14, 20]: The captured piece, if any.
    //   * Bits [21, 27]: The previous half move count.
    //   * Bits [28, 34]: The promoted piece, if any.
    //
    // TODO(aryann): Find a more efficient encoding.
    std::uint64_t bits_;
};

std::ostream &operator<<(std::ostream &os, const Move &move);

} // namespace chessengine

#endif // CHESS_ENGINE_MOVE_H_
