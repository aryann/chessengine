#ifndef CHESS_ENGINE_BITBOARD_H_
#define CHESS_ENGINE_BITBOARD_H_

#include <format>
#include <initializer_list>
#include <string>

#include "types.h"

namespace chessengine {

// Represents an 8x8 chess board.
//
// The least significant bit is A1. The most significant bit is H8.
using Bitboard = std::uint64_t;

namespace rank {

// N.B.: Integer literals used with Bitboard must be at least 64-bit to
// prevent overflow during bitwise operations. The ULL suffix ensures the
// literal is unsigned long long, which is guaranteed to be at least 64 bits.
constexpr Bitboard k1 = 0xFFULL;
constexpr Bitboard k2 = k1 << 8;
constexpr Bitboard k3 = k2 << 8;
constexpr Bitboard k4 = k3 << 8;
constexpr Bitboard k5 = k4 << 8;
constexpr Bitboard k6 = k5 << 8;
constexpr Bitboard k7 = k6 << 8;
constexpr Bitboard k8 = k7 << 8;

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
    if constexpr (D == kNorthEast) {
        return start << 7 & ~file::kH;
    }

    if constexpr (D == kNorthWest) {
        return start << 9 & ~file::kA;
    }

    if constexpr (D == kSouthEast) {
        return start >> 9 & ~file::kH;
    }

    if constexpr (D == kSouthWest) {
        return start >> 7 & ~file::kA;
    }

    return 0ULL;
}


constexpr Bitboard ToBitboard(Square square) {
    return 1ULL << square;
}

constexpr Bitboard ToBitboard(std::initializer_list<Square> squares) {
    Bitboard bitboard = 0;
    for (Square square: squares) {
        bitboard |= 1ULL << square;
    }
    return bitboard;
}

constexpr Bitboard Set(Bitboard bitboard, Square square) {
    return bitboard | ToBitboard(square);
}

inline bool GetBit(Bitboard bitboard, Square square) {
    return bitboard & (1ULL << square);
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

        for (int rank = 7; rank >= 0; --rank) {
            out = std::format_to(out, "{}:", rank + 1);
            for (int file = 0; file < 8; ++file) {
                auto square = static_cast<chessengine::Square>(rank * 8 + file);
                if (chessengine::GetBit(bitboard, square)) {
                    out = std::format_to(out, " X");
                } else {
                    out = std::format_to(out, " .");
                }
            }
            out = std::format_to(out, "\n");
        }

        out = std::format_to(out, "  ");
        for (int file = 0; file < 8; ++file) {
            out = std::format_to(out, " {:c}", 'a' + file);
        }
        out = std::format_to(out, "\n");

        return out;
    }
};

#endif // CHESS_ENGINE_BITBOARD_H_

