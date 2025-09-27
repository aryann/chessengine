#ifndef CHESS_ENGINE_BITBOARD_H_
#define CHESS_ENGINE_BITBOARD_H_

#include <cstdint>
#include <format>
#include <initializer_list>
#include <string>

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


enum Square : std::uint8_t {
    A1, A2, A3, A4, A5, A6, A7, A8,
    B1, B2, B3, B4, B5, B6, B7, B8,
    C1, C2, C3, C4, C5, C6, C7, C8,
    D1, D2, D3, D4, D5, D6, D7, D8,
    E1, E2, E3, E4, E5, E6, E7, E8,
    F1, F2, F3, F4, F5, F6, F7, F8,
    G1, G2, G3, G4, G5, G6, G7, G8,
    H1, H2, H3, H4, H5, H6, H7, H8,
};

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

