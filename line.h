#ifndef CHESS_ENGINE_LINE_H_
#define CHESS_ENGINE_LINE_H_

#include "bitboard.h"
#include "types.h"

namespace chessengine {

template<Direction Direction>
consteval void GenerateLines(Square from, std::array<Bitboard, kNumSquares> &lines) {
    Bitboard result(from);
    Bitboard curr(from);

    while (curr) {
        Square to = curr.LeastSignificantBit();
        lines[to] = result;
        curr = curr.Shift<Direction>();
        result |= curr;
    }
}

consteval auto GenerateLines() {
    std::array<std::array<Bitboard, kNumSquares>, kNumSquares> lines;

    for (int square = A8; square < kNumSquares; ++square) {
        Square from = static_cast<Square>(square);
        std::array<Bitboard, kNumSquares> &curr = lines[square];

        GenerateLines<kNorth>(from, curr);
        GenerateLines<kNorthEast>(from, curr);
        GenerateLines<kEast>(from, curr);
        GenerateLines<kSouthEast>(from, curr);
        GenerateLines<kSouth>(from, curr);
        GenerateLines<kSouthWest>(from, curr);
        GenerateLines<kWest>(from, curr);
        GenerateLines<kNorthWest>(from, curr);
    }

    return lines;
}

constexpr Bitboard GetLine(Square a, Square b) {
    static constexpr std::array<std::array<Bitboard, kNumSquares>, kNumSquares> kLines = GenerateLines();
    return kLines[a][b];
}

} // namespace chessengine

#endif // CHESS_ENGINE_LINE_H_
