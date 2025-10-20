#ifndef CHESS_ENGINE_MOVE_H_
#define CHESS_ENGINE_MOVE_H_

#include "absl/log/check.h"
#include "types.h"

namespace chessengine {

class Move {
public:
    explicit constexpr Move(Square from, Square to) :
        data_(from + (to << 6)) {
    }

    constexpr Move(Square from, Square to, Piece promoted_piece):
        Move(from, to) {
        DCHECK(
                promoted_piece == kKnight ||
                promoted_piece == kBishop ||
                promoted_piece == kRook ||
                promoted_piece == kQueen);
        DCHECK(kBishop - kKnight == 1);
        DCHECK(kRook - kKnight == 2);
        DCHECK(kQueen - kKnight == 3);

        int flags = static_cast<int>(kPromotionFlag) | (promoted_piece - kKnight);
        data_ += flags << 12;
    }

    [[nodiscard]] constexpr Square from() const {
        return static_cast<Square>(data_ & 0b111111);
    }

    [[nodiscard]] constexpr Square to() const {
        return static_cast<Square>((data_ >> 6) & 0b111111);
    }

    [[nodiscard]] constexpr bool IsPromotion() const {
        return GetFlags() & kPromotionFlag;
    }

    [[nodiscard]] constexpr Piece GetPromotedPiece() const {
        DCHECK(IsPromotion());
        return static_cast<Piece>((GetFlags() & 0b11) + kKnight);
    }

    constexpr auto operator<=>(const Move &other) const = default;

private:
    [[nodiscard]] constexpr std::uint8_t GetFlags() const {
        return data_ >> 12;
    }


    // The two lower bits of this flag are reserved for the four piece types
    // (knight, bishop, rook, and queen).
    //
    // This scheme is forward-compatible with the scheme documented at
    // https://www.chessprogramming.org/Encoding_Moves.
    constexpr static std::uint8_t kPromotionFlag = 0b1000;

    // Stores the move state:
    //
    //   * Bits [0,   6): The `from` Square.
    //   * Bits [6,  12): The `to` Square.
    //   * Bits [12, 16): Flags.
    //
    // TODO(aryann): Find a more efficient encoding.
    std::uint16_t data_;
};

std::ostream &operator<<(std::ostream &os, const Move &move);

struct UndoInfo {
    Move move;
    Piece captured_piece;
    std::uint8_t previous_half_moves;
};

} // namespace chessengine

#endif // CHESS_ENGINE_MOVE_H_
