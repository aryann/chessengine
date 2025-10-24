#ifndef CHESS_ENGINE_MOVE_H_
#define CHESS_ENGINE_MOVE_H_

#include <expected>

#include "castling.h"
#include "absl/log/check.h"
#include "types.h"

namespace chessengine {

class Move {
public:
    // This scheme is forward-compatible with the scheme documented at
    // https://www.chessprogramming.org/Encoding_Moves.
    enum Flags : std::uint8_t {
        kCastle = /*       */ 0b0010,
        kPromotionFlag = /**/ 0b1000,
    };

    explicit constexpr Move(Square from, Square to, std::uint8_t flags = 0) :
        data_(from + (to << 6) + (flags << 12)) {
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

    static std::expected<Move, std::string> FromUCI(std::string_view input);

    [[nodiscard]] constexpr Square from() const {
        return static_cast<Square>(data_ & 0b111111);
    }

    [[nodiscard]] constexpr Square to() const {
        return static_cast<Square>((data_ >> 6) & 0b111111);
    }

    [[nodiscard]] constexpr bool IsCastling() const {
        return GetFlags() == kCastle;
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

constexpr std::optional<Square> GetEnPassantTargetFromMove(Piece piece, const Move &move) {
    if (piece != kPawn) {
        return std::nullopt;
    }

    int diff = move.to() - move.from();
    if (diff == 16) {
        return static_cast<Square>(move.from() + 8);
    }
    if (diff == -16) {
        return static_cast<Square>(move.from() - 8);
    }
    return std::nullopt;
}

struct UndoInfo {
    Move move;
    std::optional<Square> en_passant_target;
    Piece captured_piece;
    std::uint8_t half_moves;
    CastlingRights castling_rights;
};

static_assert(sizeof(UndoInfo) == 8,
              "UndoInfo size is not 8 bytes! "
              "Check field ordering for padding or new members.");

static_assert(alignof(UndoInfo) == 2,
              "UndoInfo alignment is not 2 bytes! "
              "Check for new members with larger alignment.");

} // namespace chessengine

#endif // CHESS_ENGINE_MOVE_H_
