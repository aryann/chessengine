#include "move_generator.h"

#include <vector>

#include "attacks.h"
#include "types.h"

namespace chessengine {
namespace {

void AddPawnPushes(Bitboard destinations, int offset, std::vector<Move> &moves) {
    while (destinations) {
        Square to = destinations.PopLeastSignificantBit();
        Square from = static_cast<Square>(to - offset);
        moves.emplace_back(from, to);
    }
}

template<Side Side, MoveType MoveType>
void GeneratePawnMoves(const Position &position, std::vector<Move> &moves) {
    constexpr Direction forward = Side == kWhite ? kNorth : kSouth;
    Bitboard second_rank = Side == kWhite ? rank::k3 : rank::k6;
    Bitboard pre_promotion_rank = Side == kWhite ? rank::k7 : rank::k2;
    Bitboard empty_squares = ~position.GetPieces();

    Bitboard unpromotable_pawns = position.GetPieces(position.SideToMove(), kPawn) & ~pre_promotion_rank;

    if (MoveType == kQuiet) {
        Bitboard single_moves = unpromotable_pawns.Shift<forward>() & empty_squares;
        AddPawnPushes(single_moves, forward, moves);

        Bitboard double_moves = (single_moves & second_rank).Shift<forward>() & empty_squares;
        AddPawnPushes(double_moves, forward * 2, moves);
    }
}

template<Side Side, Piece Piece>
void GenerateMoves(const Position &position, Bitboard targets, std::vector<Move> &moves) {
    Bitboard pieces = position.GetPieces(Side, Piece);

    while (pieces) {
        Square from = pieces.PopLeastSignificantBit();
        Bitboard attacks = GenerateAttacks<Piece>(from, position.GetPieces()) & targets;

        while (attacks) {
            Square to = attacks.PopLeastSignificantBit();
            moves.emplace_back(from, to);
        }
    }
}

template<MoveType MoveType>
Bitboard GetTargets(const Position &position) {
    if constexpr (MoveType == kQuiet) {
        return ~position.GetPieces();
    }

    if constexpr (MoveType == kCapture) {
        return position.GetPieces(~position.SideToMove());
    }

    return {};
}

template<Side Side, MoveType MoveType>
std::vector<Move> GenerateAllMoves(const Position &position) {
    static_assert(MoveType == kQuiet || MoveType == kCapture);

    Bitboard targets = GetTargets<MoveType>(position);

    std::vector<Move> moves;
    GeneratePawnMoves<Side, MoveType>(position, moves);
    GenerateMoves<Side, kKnight>(position, targets, moves);
    GenerateMoves<Side, kBishop>(position, targets, moves);
    GenerateMoves<Side, kRook>(position, targets, moves);
    GenerateMoves<Side, kQueen>(position, targets, moves);
    GenerateMoves<Side, kKing>(position, targets, moves);
    return moves;
}

} // namespace

template<MoveType MoveType>
std::vector<Move> GenerateMoves(const Position &position) {
    static_assert(MoveType == kQuiet || MoveType == kCapture);

    if (position.SideToMove() == kWhite) {
        return GenerateAllMoves<kWhite, MoveType>(position);
    } else {
        return GenerateAllMoves<kBlack, MoveType>(position);
    }
}

// Explicitly instantiate the templates for `GenerateMoves()`.
// This ensures the function is compiled and available to the linker, as the
// template's definition is in this .cc file rather than a header.
template
std::vector<Move> GenerateMoves<kQuiet>(const Position &position);

template
std::vector<Move> GenerateMoves<kCapture>(const Position &position);

} // namespace chessengine
