#ifndef CHESS_ENGINE_POSITION_H_
#define CHESS_ENGINE_POSITION_H_

#include <expected>
#include <string_view>

#include "bitboard.h"
#include "types.h"

namespace chessengine {

class Position {
public:
    static Position Make();

    // Parses a Forsyth–Edwards Notation (FEN) string to create a `Position`.
    //
    // Returns an error string with a descriptive message if and only if the FEN
    // value is invalid.
    static std::expected<Position, std::string> Make(std::string_view fen);

    // Returns the piece at the given square.
    [[nodiscard]] Piece piece(Square square) const;

    // Returns the side at the given square.
    [[nodiscard]] Side side(Square square) const;

private:
    Position() = default;

    std::array<Bitboard, kNumPieces> pieces_;
    std::array<Bitboard, kNumSides> sides_;

    Side side_to_move_;
    std::optional<Square> en_passant_target_;

    // TODO(aryann): Add castling rights.

    int half_moves_;
    int full_moves_;
};

} // namespace chessengine

template<>
struct std::formatter<chessengine::Position> : std::formatter<std::string> {
    static auto format(chessengine::Position position, std::format_context &context) {

        auto GetSquare = [&](chessengine::Square square) {
            static char kPieceChars[] = {'P', 'p', 'N', 'B', 'R', 'Q', 'K', '.', '.'};
            char result = kPieceChars[static_cast<int>(position.piece(square))];

            if (position.side(square) == chessengine::kBlack) {
                result = std::tolower(result);
            }
            return result;
        };

        auto out = context.out();

        for (int row = 0; row < 8; ++row) {
            out = std::format_to(out, "{}:", 8 - row);
            for (int col = 0; col < 8; ++col) {
                auto square = static_cast<chessengine::Square>(row * 8 + col);
                out = std::format_to(out, " {}", GetSquare(square));
            }

            out = std::format_to(out, "\n");
        }

        out = std::format_to(out, "  ");
        for (int col = 0; col < 8; ++col) {
            out = std::format_to(out, " {:c}", 'a' + col);
        }
        out = std::format_to(out, "\n\n");
        out = std::format_to(out, "      Turn: -\n");
        out = std::format_to(out, "  Castling: -\n");
        out = std::format_to(out, "En Passant: -\n");
        out = std::format_to(out, "Half Moves: 0\n");
        out = std::format_to(out, "Full Moves: 0\n");
        return out;
    }
};

#endif // CHESS_ENGINE_POSITION_H_

