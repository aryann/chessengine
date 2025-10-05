#include "move_generator.h"

#include <vector>

#include "attacks.h"
#include "types.h"

namespace chessengine {
namespace {

template<Piece Piece>
void GenerateMoves(const Position &position, Bitboard targets, std::vector<Move> &moves) {
    Bitboard pieces = position.Pieces(position.SideToMove(), Piece);

    while (pieces) {
        Square from = pieces.PopLeastSignificantBit();
        Bitboard attacks = kPseudoAttacks[Piece][from] & targets;

        while (attacks) {
            Square to = attacks.PopLeastSignificantBit();
            moves.emplace_back(from, to);
        }
    }
}

template<MoveType MoveType>
Bitboard GetTargets(const Position &position) {
    if constexpr (MoveType == kQuiet) {
        return ~position.Pieces();
    }

    if constexpr (MoveType == kCapture) {
        return position.Pieces(~position.SideToMove());
    }

    return {};
}

} // namespace

template<MoveType MoveType>
std::vector<Move> GenerateMoves(const Position &position) {
    static_assert(MoveType == kQuiet || MoveType == kCapture);

    Bitboard targets = GetTargets<MoveType>(position);

    std::vector<Move> moves;
    GenerateMoves<kKnight>(position, targets, moves);
    return moves;
}

} // namespace chessengine
