#include "move_generator.h"

#include <vector>

#include "absl/log/check.h"
#include "attacks.h"
#include "line.h"
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

void AddPawnPromotions(Bitboard promotions, int offset, std::vector<Move> &moves) {
    while (promotions) {
        Square to = promotions.PopLeastSignificantBit();
        Square from = static_cast<Square>(to - offset);

        moves.emplace_back(from, to, MoveOptions().SetPromoted(kQueen));
        moves.emplace_back(from, to, MoveOptions().SetPromoted(kRook));
        moves.emplace_back(from, to, MoveOptions().SetPromoted(kKnight));
        moves.emplace_back(from, to, MoveOptions().SetPromoted(kBishop));
    }
}

void AddPawnCaptures(Bitboard captures, int offset, const Position &position, std::vector<Move> &moves) {
    while (captures) {
        Square to = captures.PopLeastSignificantBit();
        Square from = static_cast<Square>(to - offset);

        moves.emplace_back(from, to, MoveOptions().SetCaptured(position.GetPiece(to), position.GetHalfMoves()));
    }
}

template<Side Side, MoveType MoveType>
void GeneratePawnMoves(const Position &position, std::vector<Move> &moves) {
    constexpr Direction forward = Side == kWhite ? kNorth : kSouth;
    Bitboard second_rank = Side == kWhite ? rank::k3 : rank::k6;
    Bitboard promotion_rank = Side == kWhite ? rank::k7 : rank::k2;
    Bitboard empty_squares = ~position.GetPieces();

    Bitboard pawns = position.GetPieces(position.SideToMove(), kPawn);
    Bitboard unpromotable_pawns = pawns & ~promotion_rank;
    Bitboard promotable_pawns = pawns & promotion_rank;

    if constexpr (MoveType == kQuiet) {
        Bitboard single_moves = unpromotable_pawns.Shift<forward>() & empty_squares;
        AddPawnPushes(single_moves, forward, moves);

        Bitboard double_moves = (single_moves & second_rank).Shift<forward>() & empty_squares;
        AddPawnPushes(double_moves, forward * 2, moves);

        Bitboard prompted_pawns = promotable_pawns.Shift<forward>() & empty_squares;
        AddPawnPromotions(prompted_pawns, forward, moves);
    }

    if constexpr (MoveType == kCapture) {
        constexpr Direction left = Side == kWhite ? kNorthWest : kSouthEast;
        constexpr Direction right = Side == kWhite ? kNorthEast : kSouthWest;
        Bitboard enemies = position.GetPieces(~Side);

        Bitboard left_captures = unpromotable_pawns.Shift<left>() & enemies;
        Bitboard right_captures = unpromotable_pawns.Shift<right>() & enemies;

        AddPawnCaptures(left_captures, left, position, moves);
        AddPawnCaptures(right_captures, right, position, moves);
    }
}

template<Side Side, MoveType MoveType, Piece Piece>
void GenerateMoves(const Position &position, Bitboard targets, std::vector<Move> &moves) {
    Bitboard pieces = position.GetPieces(Side, Piece);

    while (pieces) {
        Square from = pieces.PopLeastSignificantBit();
        Bitboard attacks = GenerateAttacks<Piece>(from, position.GetPieces()) & targets;

        while (attacks) {
            Square to = attacks.PopLeastSignificantBit();

            MoveOptions options;
            if constexpr (MoveType == kCapture || MoveType == kEvasion) {
                if (position.GetPiece(to) != kEmptyPiece) {
                    options.SetCaptured(position.GetPiece(to), position.GetHalfMoves());
                }
            }
            moves.emplace_back(from, to, options);
        }
    }
}

template<Side Side, MoveType MoveType>
Bitboard GetTargets(const Position &position) {
    if constexpr (MoveType == kQuiet) {
        return ~position.GetPieces();
    }

    if constexpr (MoveType == kCapture) {
        return position.GetPieces(~Side);
    }

    if constexpr (MoveType == kEvasion) {
        Bitboard checkers = position.GetCheckers();
        return GetLine(position.GetKing(), checkers.LeastSignificantBit()) & ~Bitboard(position.GetKing());
    }

    return {};
}

template<Side Side, MoveType MoveType>
std::vector<Move> GenerateMoves(const Position &position) {
    std::vector<Move> moves;
    Bitboard targets = GetTargets<Side, MoveType>(position);

    if (MoveType != kEvasion || !position.GetCheckers().HasMoreThanOneBit()) {
        GeneratePawnMoves<Side, MoveType>(position, moves);
        GenerateMoves<Side, MoveType, kKnight>(position, targets, moves);
        GenerateMoves<Side, MoveType, kBishop>(position, targets, moves);
        GenerateMoves<Side, MoveType, kRook>(position, targets, moves);
        GenerateMoves<Side, MoveType, kQueen>(position, targets, moves);
    }

    if constexpr (MoveType == kEvasion) {
        // If the move type is an evasion, then the king should be allowed to move
        // to any square that is not occupied by its own side.
        targets = ~position.GetPieces(Side);
    }

    GenerateMoves<Side, MoveType, kKing>(position, targets, moves);
    return moves;
}

} // namespace

template<MoveType MoveType>
std::vector<Move> GenerateMoves(const Position &position) {
    if (position.SideToMove() == kWhite) {
        return GenerateMoves<kWhite, MoveType>(position);
    } else {
        return GenerateMoves<kBlack, MoveType>(position);
    }
}

// Explicitly instantiate the templates for `GenerateMoves()`.
// This ensures the function is compiled and available to the linker, as the
// template's definition is in this .cc file rather than a header.
template
std::vector<Move> GenerateMoves<kQuiet>(const Position &position);

template
std::vector<Move> GenerateMoves<kCapture>(const Position &position);

template
std::vector<Move> GenerateMoves<kEvasion>(const Position &position);

} // namespace chessengine
