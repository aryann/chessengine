#ifndef CHESS_ENGINE_ATTACKS_H_
#define CHESS_ENGINE_ATTACKS_H_

#include <array>

#include "bitboard.h"

namespace chessengine {

consteval auto MakePseudoAttacks() {
    std::array<std::array<Bitboard, NUM_SQUARES>, NUM_PIECES> attacks{};
    return attacks;
}

inline constexpr auto kPseudoAttacks = MakePseudoAttacks();

} // namespace chessengine

#endif // CHESS_ENGINE_ATTACKS_H_
