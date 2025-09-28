#ifndef CHESS_ENGINE_BITBOARD_H_
#define CHESS_ENGINE_BITBOARD_H_

#include <format>
#include <initializer_list>
#include <string>

#include "types.h"

namespace chessengine {

// Represents an 8x8 chess board.
//
// Squares map to bits in the bitboard as follows, with square A8 corresponding
// to the least significant bit (LSB), and H1 to the most significant bit (MSB).
//
//   8:   0   1   2   3   4   5   6   7
//   7:   8   9  10  11  12  13  14  15
//   6:  16  17  18  19  20  21  22  23
//   5:  24  25  26  27  28  29  30  31
//   4:  32  33  34  35  36  37  38  39
//   3:  40  41  42  43  44  45  46  47
//   2:  48  49  50  51  52  53  54  55
//   1:  56  57  58  59  60  61  62  63
//       a   b   c   d   e   f   g   h
//
// This layout matches the typical visual representation of a board, improving
// code readability and debuggability.
using Bitboard = std::uint64_t;

constexpr Bitboard kEmptyBoard = 0ULL;

namespace rank {

// N.B.: Integer literals used with Bitboard must be at least 64-bit to
// prevent overflow during bitwise operations. The ULL suffix ensures the
// literal is unsigned long long, which is guaranteed to be at least 64 bits.
constexpr Bitboard k8 = 0xFFULL;
constexpr Bitboard k7 = k8 << 8;
constexpr Bitboard k6 = k7 << 8;
constexpr Bitboard k5 = k6 << 8;
constexpr Bitboard k4 = k5 << 8;
constexpr Bitboard k3 = k4 << 8;
constexpr Bitboard k2 = k3 << 8;
constexpr Bitboard k1 = k2 << 8;

} // rank

namespace file {

constexpr Bitboard kA = 0x101010101010101ULL;
constexpr Bitboard kB = kA << 1;
constexpr Bitboard kC = kB << 1;
constexpr Bitboard kD = kC << 1;
constexpr Bitboard kE = kD << 1;
constexpr Bitboard kF = kE << 1;
constexpr Bitboard kG = kF << 1;
constexpr Bitboard kH = kG << 1;

} // file

template<Direction D>
constexpr Bitboard Shift(Bitboard start) {
    if constexpr (D == kNorth) {
        return start >> 8;
    }

    if constexpr (D == kNorthEast) {
        return start >> 7 & ~file::kA;
    }

    if constexpr (D == kEast) {
        return start << 1 & ~file::kA;
    }

    if constexpr (D == kSouthEast) {
        return start << 9 & ~file::kA;
    }
    if constexpr (D == kSouth) {
        return start << 8;
    }

    if constexpr (D == kSouthWest) {
        return start << 7 & ~file::kH;
    }

    if constexpr (D == kWest) {
        return start >> 1 & ~file::kH;
    }

    if constexpr (D == kNorthWest) {
        return start >> 9 & ~file::kH;
    }

    return kEmptyBoard;
}


constexpr Bitboard ToBitboard(Square square) {
    return 1ULL << square;
}

constexpr Bitboard ToBitboard(std::initializer_list<Square> squares) {
    Bitboard bitboard = kEmptyBoard;
    for (Square square: squares) {
        bitboard |= 1ULL << square;
    }
    return bitboard;
}

constexpr bool Get(Bitboard bitboard, Square square) {
    return bitboard & (1ULL << square);
}

constexpr Bitboard Set(Bitboard bitboard, Square square) {
    return bitboard | ToBitboard(square);
}

constexpr Bitboard Clear(Bitboard bitboard, Square square) {
    return bitboard & (~ToBitboard(square));
}

} // namespace chessengine

// A std::formatter specialization for printing a Bitboard.
//
// See https://en.cppreference.com/w/cpp/utility/format/formatter.html for
// more details.
template<>
struct std::formatter<chessengine::Bitboard> : std::formatter<std::string> {
    static auto format(chessengine::Bitboard bitboard, std::format_context &context) {
        auto out = context.out();

        for (int row = 0; row < 8; ++row) {
            out = std::format_to(out, "{}:", 8 - row);
            for (int col = 0; col < 8; ++col) {
                auto square = static_cast<chessengine::Square>(row * 8 + col);
                if (chessengine::Get(bitboard, square)) {
                    out = std::format_to(out, " X");
                } else {
                    out = std::format_to(out, " .");
                }
            }
            out = std::format_to(out, "\n");
        }

        out = std::format_to(out, "  ");
        for (int col = 0; col < 8; ++col) {
            out = std::format_to(out, " {:c}", 'a' + col);
        }
        out = std::format_to(out, "\n");

        return out;
    }
};

#endif // CHESS_ENGINE_BITBOARD_H_

