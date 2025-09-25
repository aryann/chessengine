#ifndef CHESS_ENGINE_BITBOARD_H_
#define CHESS_ENGINE_BITBOARD_H_

#include <cstdint>
#include <initializer_list>

namespace chessengine {

// Represents an 8x8 chess board.
//
// The least significant bit is A1. The most significant bit is H8.
using Bitboard = std::uint64_t;

namespace file {

constexpr Bitboard kA = 0xFF;
constexpr Bitboard kB = kA << 8;
constexpr Bitboard kC = kB << 8;
constexpr Bitboard kD = kC << 8;
constexpr Bitboard kE = kD << 8;
constexpr Bitboard kF = kE << 8;
constexpr Bitboard kG = kF << 8;
constexpr Bitboard kH = kG << 8;

} // file

namespace rank {

constexpr Bitboard k1 = 0x101010101010101;
constexpr Bitboard k2 = k1 << 1;
constexpr Bitboard k3 = k2 << 1;
constexpr Bitboard k4 = k3 << 1;
constexpr Bitboard k5 = k4 << 1;
constexpr Bitboard k6 = k5 << 1;
constexpr Bitboard k7 = k6 << 1;
constexpr Bitboard k8 = k7 << 1;

} // rank

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
    return 1 << square;
}

constexpr Bitboard ToBitboard(std::initializer_list<Square> squares) {
    Bitboard bitboard = 0;
    for (Square square: squares) {
        bitboard |= 1 << square;
    }
    return bitboard;
}


} // namespace chessengine

#endif // CHESS_ENGINE_BITBOARD_H_

