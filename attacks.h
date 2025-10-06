#ifndef CHESS_ENGINE_ATTACKS_H_
#define CHESS_ENGINE_ATTACKS_H_

#include <array>

#include "bitboard.h"

namespace chessengine {

consteval void MakeWhitePawnAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A8; square < A1; ++square) {
        Bitboard start(static_cast<Square>(square));
        attacks[square] = kEmptyBoard
                          | start.Shift<kNorthEast>()
                          | start.Shift<kNorthWest>();
    }
}

consteval void MakeBlackPawnAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A7; square < kNumSquares; ++square) {
        Bitboard start(static_cast<Square>(square));
        attacks[square] = kEmptyBoard
                          | start.Shift<kSouthEast>()
                          | start.Shift<kSouthWest>();
    }
}

consteval void MakeKnightAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A8; square < kNumSquares; ++square) {
        Bitboard start(static_cast<Square>(square));
        attacks[square] = kEmptyBoard
                          | start.Shift<kNorth>().Shift<kNorthEast>()
                          | start.Shift<kEast>().Shift<kNorthEast>()
                          | start.Shift<kEast>().Shift<kSouthEast>()
                          | start.Shift<kSouth>().Shift<kSouthEast>()
                          | start.Shift<kSouth>().Shift<kSouthWest>()
                          | start.Shift<kWest>().Shift<kSouthWest>()
                          | start.Shift<kWest>().Shift<kNorthWest>()
                          | start.Shift<kNorth>().Shift<kNorthWest>();
    }
}

// Returns a bitboard representing a ray from the `from` square in the given
// `Direction`. The ray extends to the edge of the board, but the `from`
// square is not included.
template<Direction Direction>
consteval Bitboard MakeRay(Square from) {
    Bitboard result;
    Bitboard curr(from);
    while (curr) {
        curr = curr.Shift<Direction>();
        result |= curr;
    }
    return result;
}

consteval void MakeBishopAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A8; square < kNumSquares; ++square) {
        Square start = static_cast<Square>(square);

        attacks[square] = kEmptyBoard
                          | MakeRay<kNorthEast>(start)
                          | MakeRay<kSouthEast>(start)
                          | MakeRay<kSouthWest>(start)
                          | MakeRay<kNorthWest>(start);
    }
}

consteval void MakeKingAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A8; square < kNumSquares; ++square) {
        Bitboard start(static_cast<Square>(square));
        attacks[square] = kEmptyBoard
                          | start.Shift<kNorth>()
                          | start.Shift<kNorthEast>()
                          | start.Shift<kEast>()
                          | start.Shift<kSouthEast>()
                          | start.Shift<kSouth>()
                          | start.Shift<kSouthWest>()
                          | start.Shift<kWest>()
                          | start.Shift<kNorthWest>();
    }
}

consteval auto MakePseudoAttacks() {
    std::array<std::array<Bitboard, kNumSquares>, kNumPieces> attacks{};

    MakeWhitePawnAttacks(attacks[kWhitePawn]);
    MakeBlackPawnAttacks(attacks[kBlackPawn]);
    MakeKnightAttacks(attacks[kKnight]);
    MakeBishopAttacks(attacks[kBishop]);
    MakeKingAttacks(attacks[kKing]);
    return attacks;
}

// N.B.: Since MakePseudoAttacks() is consteval, the attack array will be
// evaluated at compile time.
inline constexpr auto kPseudoAttacks = MakePseudoAttacks();

} // namespace chessengine

#endif // CHESS_ENGINE_ATTACKS_H_
