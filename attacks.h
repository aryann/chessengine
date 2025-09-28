#ifndef CHESS_ENGINE_ATTACKS_H_
#define CHESS_ENGINE_ATTACKS_H_

#include <array>

#include "bitboard.h"

namespace chessengine {

consteval void MakeWhitePawnAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A8; square < A1; ++square) {
        Bitboard start = ToBitboard(static_cast<Square>(square));
        attacks[square] = kEmptyBoard
                          | Shift<kNorthEast>(start)
                          | Shift<kNorthWest>(start);
    }
}

consteval void MakeBlackPawnAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A7; square < kNumSquares; ++square) {
        Bitboard start = ToBitboard(static_cast<Square>(square));
        attacks[square] = kEmptyBoard
                          | Shift<kSouthEast>(start)
                          | Shift<kSouthWest>(start);
    }
}

consteval void MakeKnightAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A8; square < kNumSquares; ++square) {
        Bitboard start = ToBitboard(static_cast<Square>(square));
        attacks[square] = kEmptyBoard
                          | Shift<kNorth>(Shift<kNorthEast>(start))
                          | Shift<kEast>(Shift<kNorthEast>(start))
                          | Shift<kEast>(Shift<kSouthEast>(start))
                          | Shift<kSouth>(Shift<kSouthEast>(start))
                          | Shift<kSouth>(Shift<kSouthWest>(start))
                          | Shift<kWest>(Shift<kSouthWest>(start))
                          | Shift<kWest>(Shift<kNorthWest>(start))
                          | Shift<kNorth>(Shift<kNorthWest>(start));
    }
}

consteval void MakeKingAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A8; square < kNumSquares; ++square) {
        Bitboard start = ToBitboard(static_cast<Square>(square));
        attacks[square] = kEmptyBoard
                          | Shift<kNorth>(start)
                          | Shift<kNorthEast>(start)
                          | Shift<kEast>(start)
                          | Shift<kSouthEast>(start)
                          | Shift<kSouth>(start)
                          | Shift<kSouthWest>(start)
                          | Shift<kWest>(start)
                          | Shift<kNorthWest>(start);
    }
}

consteval auto MakePseudoAttacks() {
    std::array<std::array<Bitboard, kNumSquares>, kNumPieces> attacks{};

    MakeWhitePawnAttacks(attacks[kWhitePawn]);
    MakeBlackPawnAttacks(attacks[kBlackPawn]);
    MakeKnightAttacks(attacks[kKnight]);
    MakeKingAttacks(attacks[kKing]);
    return attacks;
}

// N.B.: Since MakePseudoAttacks() is consteval, the attack array will be
// evaluated at compile time.
inline constexpr auto kPseudoAttacks = MakePseudoAttacks();

} // namespace chessengine

#endif // CHESS_ENGINE_ATTACKS_H_
