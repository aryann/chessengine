#ifndef CHESS_ENGINE_POSITION_H_
#define CHESS_ENGINE_POSITION_H_

#include <expected>
#include <string_view>

#include "bitboard.h"
#include "types.h"

namespace chessengine {

class Position {
public:
    Position();

    // Parses a Forsyth–Edwards Notation (FEN) string to create a `Position`.
    //
    // Returns an error string with a descriptive message if and only if the FEN
    // value is invalid.
    static std::expected<Position, std::string> Make(std::string_view fen);

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

