#include "move_generator.h"

#include <vector>

#include "absl/log/check.h"
#include "attacks.h"
#include "line.h"
#include "types.h"

namespace chessengine {
namespace {

void AddPawnMoves(Bitboard destinations, int offset, std::vector<Move> &moves) {
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

        moves.emplace_back(from, to, Move::Flags::kKnightPromotion);
        moves.emplace_back(from, to, Move::Flags::kBishopPromotion);
        moves.emplace_back(from, to, Move::Flags::kRookPromotion);
        moves.emplace_back(from, to, Move::Flags::kQueenPromotion);
    }
}

template<Side Side, MoveType MoveType>
void GeneratePawnMoves(const Position &position, std::vector<Move> &moves) {
    static constexpr Direction forward = Side == kWhite ? kNorth : kSouth;
    static constexpr Bitboard promotion_rank = Side == kWhite ? rank::k8 : rank::k1;
    Bitboard pawns = position.GetPieces(position.SideToMove(), kPawn);

    if constexpr (MoveType == kQuiet || MoveType == kEvasion) {
        Bitboard empty = ~position.GetPieces();

        // Single pawn pushes:
        Bitboard single_moves = pawns.Shift<forward>() & empty;
        AddPawnMoves(single_moves & ~promotion_rank, forward, moves);
        AddPawnPromotions(single_moves & promotion_rank, forward, moves);

        // Double pawn pushes:
        Bitboard second_rank = Side == kWhite ? rank::k3 : rank::k6;
        Bitboard double_moves = (single_moves & second_rank).Shift<forward>() & empty;
        AddPawnMoves(double_moves, forward * 2, moves);
    }

    if constexpr (MoveType == kCapture || MoveType == kEvasion) {
        Bitboard enemies = position.GetPieces(~Side);
        std::optional<Square> en_passant_target = position.GetEnPassantTarget();
        if (en_passant_target) {
            enemies.Set(*en_passant_target);
        }

        constexpr Direction left = Side == kWhite ? kNorthWest : kSouthEast;
        constexpr Direction right = Side == kWhite ? kNorthEast : kSouthWest;

        Bitboard left_captures = pawns.Shift<left>() & enemies;
        Bitboard right_captures = pawns.Shift<right>() & enemies;

        AddPawnMoves(left_captures & ~promotion_rank, left, moves);
        AddPawnMoves(right_captures & ~promotion_rank, right, moves);

        AddPawnPromotions(left_captures & promotion_rank, left, moves);
        AddPawnPromotions(right_captures & promotion_rank, right, moves);
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
            moves.emplace_back(from, to);
        }
    }
}

template<Side Side>
[[nodiscard]] bool CanCastle(const Position &position, Bitboard path) {
    if (position.GetPieces() & path) {
        return false;
    }

    while (path) {
        Square square = path.PopLeastSignificantBit();
        if (position.GetAttackers(square, ~Side)) {
            return false;
        }
    }

    return true;
}

template<Side Side>
void GenerateCastlingMoves(const Position &position, std::vector<Move> &moves) {
    static_assert(Side == kWhite || Side == kBlack);

    if (position.GetCastlingRights().HasKingSide<Side>() &&
        CanCastle<Side>(position, GetKingSideCastlingPath<Side>())) {
        static constexpr Move kCastlingMoves[] = {
                Move(E1, G1, Move::Flags::kKingCastle),
                Move(E8, G8, Move::Flags::kKingCastle),
        };
        moves.push_back(kCastlingMoves[Side]);
    }

    if (position.GetCastlingRights().HasQueenSide<Side>() &&
        CanCastle<Side>(position, GetQueenSideCastlingPath<Side>())) {
        static constexpr Move kCastlingMoves[] = {
                Move(E1, C1, Move::Flags::kQueenCastle),
                Move(E8, C8, Move::Flags::kQueenCastle),
        };
        moves.push_back(kCastlingMoves[Side]);
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
        Square from = position.GetCheckers(Side).LeastSignificantBit();
        Square to = position.GetKing(Side);
        return GetLine(from, to);
    }

    return {};
}

template<Side Side, MoveType MoveType>
std::vector<Move> GenerateMoves(const Position &position) {
    std::vector<Move> moves;
    Bitboard targets = GetTargets<Side, MoveType>(position);

    // Generate moves for all non-king pieces. This logic is shared for two
    // main scenarios:
    //
    //   1. Normal Moves (MoveType == kQuiet || MoveType == kCapture):
    //      The `targets` bitboard is set to all empty squares (for quiet)
    //      or all enemy pieces (for captures), and we generate all moves.
    //
    //   2. Evasion Moves (position.GetCheckers().GetCount() == 1):
    //      This block only runs if there is *exactly one* checker. In a
    //      double check, only the king can move, so this is skipped.
    //
    //      When MoveType is kEvasion, `GetTargets()` returns a bitboard of
    //      *only* the squares between the checker and the king (excluding
    //      the king square itself). This causes the piece generators to find
    //      all legal moves where a friendly piece blocks the check.
    //
    if (MoveType == kQuiet || MoveType == kCapture || position.GetCheckers(Side).GetCount() == 1) {
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

    if constexpr (MoveType == kQuiet) {
        GenerateCastlingMoves<Side>(position, moves);
    }

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
