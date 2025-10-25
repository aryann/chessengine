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
        kQuietMove = /*             */ 0b0000,
        kKingCastle = /*            */ 0b0010,
        kQueenCastle = /*           */ 0b0011,
        kKnightPromotion = /*       */ 0b1000,
        kBishopPromotion = /*       */ 0b1001,
        kRookPromotion = /*         */ 0b1010,
        kQueenPromotion = /*        */ 0b1011,
        kKnightPromotionCapture = /**/ 0b1100,
        kBishopPromotionCapture = /**/ 0b1101,
        kRookPromotionCapture = /*  */ 0b1110,
        kQueenPromotionCapture = /* */ 0b1111,
    };

    explicit constexpr Move(Square from, Square to, Flags flags = kQuietMove) :
        data_(from + (to << 6) + (flags << 12)) {
    }

    static std::expected<Move, std::string> FromUCI(std::string_view input);

    [[nodiscard]] constexpr Square from() const {
        return static_cast<Square>(data_ & 0b111111);
    }

    [[nodiscard]] constexpr Square to() const {
        return static_cast<Square>((data_ >> 6) & 0b111111);
    }

    [[nodiscard]] constexpr bool IsKingSideCastling() const {
        return GetFlags() == kKingCastle;
    }

    [[nodiscard]] constexpr bool IsQueenSideCastling() const {
        return GetFlags() == kQueenCastle;
    }

    [[nodiscard]] constexpr bool IsPromotion() const {
        return GetFlags() & 0b1000;
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
