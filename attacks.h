#ifndef CHESS_ENGINE_ATTACKS_H_
#define CHESS_ENGINE_ATTACKS_H_

#include <array>

#include "bitboard.h"

namespace chessengine {

consteval void MakeWhitePawnAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A2; square < A8; ++square) {
        Bitboard start = ToBitboard(static_cast<Square>(square));
        attacks[square] = (start << 7 & file::kNotH) | (start << 9 & file::kNotA);
    }
}

consteval auto MakePseudoAttacks() {
    std::array<std::array<Bitboard, kNumSquares>, kNumPieces> attacks{};

    MakeWhitePawnAttacks(attacks[kWhitePawn]);
    return attacks;
}

// N.B.: Since MakePseudoAttacks() is consteval, the attack array will be
// evaluated at compile time.
inline constexpr auto kPseudoAttacks = MakePseudoAttacks();

} // namespace chessengine

#endif // CHESS_ENGINE_ATTACKS_H_
