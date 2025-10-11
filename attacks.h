#ifndef CHESS_ENGINE_ATTACKS_H_
#define CHESS_ENGINE_ATTACKS_H_

#include <array>

#include "bitboard.h"

namespace chessengine {

template<Direction ... Directions>
consteval void MakePawnAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A8; square < kNumSquares; ++square) {
        Bitboard start(static_cast<Square>(square));
        attacks[square] = (start.Shift<Directions>() | ...);
    }
}

consteval auto MakePawnAttacks() {
    std::array<std::array<Bitboard, kNumSquares>, kNumSides> attacks;
    MakePawnAttacks<kNorthEast, kNorthWest>(attacks[kWhite]);
    MakePawnAttacks<kSouthEast, kSouthWest>(attacks[kBlack]);
    return attacks;
}

constexpr auto kPawnAttacks = MakePawnAttacks();

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

template<Direction... Directions>
consteval Bitboard MakeRays(Square from) {
    return (MakeRay<Directions>(from) | ...);
}

template<Direction ... Directions>
consteval void MakeSlidingAttacks(std::array<Bitboard, kNumSquares> &attacks) {
    for (int square = A8; square < kNumSquares; ++square) {
        attacks[square] = (MakeRay<Directions>(static_cast<Square>(square)) | ...);
    }
}

consteval auto MakePseudoAttacks() {
    std::array<std::array<Bitboard, kNumSquares>, kNumPieces> attacks;

    MakeKnightAttacks(attacks[kKnight]);
    MakeKingAttacks(attacks[kKing]);

    MakeSlidingAttacks<
        kNorthEast, kSouthEast, kSouthWest, kNorthWest>(attacks[kBishop]);

    MakeSlidingAttacks<
        kNorth, kEast, kSouth, kWest>(attacks[kRook]);

    MakeSlidingAttacks<
        kNorth, kNorthEast, kEast, kSouthEast,
        kSouth, kSouthWest, kWest, kNorthWest>(attacks[kQueen]);

    return attacks;
}

// N.B.: Since MakePseudoAttacks() is consteval, the attack array will be
// evaluated at compile time.
constexpr auto kPseudoAttacks = MakePseudoAttacks();

struct Magic {
    // Relevancy bitboard for this square and piece.
    Bitboard mask;
};

template<Direction ... Directions>
consteval std::array<Magic, kNumSquares> MakeMagic() {
    std::array<Magic, kNumSquares> result;
    for (int square = A8; square < kNumSquares; ++square) {
        Bitboard mask = (MakeRays<Directions>(static_cast<Square>(square)) | ...);
        mask &= ~kEdges;
        result[square].mask = mask;
    }
    return result;
}

template<Direction Direction>
constexpr Bitboard GenerateRayAttacks(Square from, Bitboard occupied) {
    Bitboard attacks;
    Bitboard curr(from);
    while (curr) {
        curr = curr.Shift<Direction>();
        attacks |= curr;
        if (curr & occupied) {
            break;
        }
    }
    return attacks;
}

template<Direction ... Directions>
constexpr Bitboard GenerateSlidingAttacks(Square from, Bitboard occupied) {
    return (GenerateRayAttacks<Directions>(from, occupied) | ...);
}

constexpr Bitboard GenerateBishopAttacks(Square square, Bitboard occupied) {
    static std::array<Magic, kNumSquares> kBishopMagics = MakeMagic<
        kNorthEast, kSouthEast, kSouthWest, kNorthWest>();

    occupied &= kBishopMagics[square].mask;
    return GenerateSlidingAttacks<kNorthEast, kSouthEast, kSouthWest, kNorthWest>(square, occupied);
}

constexpr Bitboard GenerateRookAttacks(Square square, Bitboard occupied) {
    static std::array<Magic, kNumSquares> kRookMagics = MakeMagic<
        kNorth, kEast, kSouth, kWest>();

    occupied &= kRookMagics[square].mask;
    return GenerateSlidingAttacks<kNorth, kEast, kSouth, kWest>(square, occupied);
}

template<Piece Piece>
constexpr Bitboard GenerateAttacks(Square square, Bitboard occupied) {
    if constexpr (Piece == kBishop) {
        return GenerateBishopAttacks(square, occupied);
    } else if constexpr (Piece == kRook) {
        return GenerateRookAttacks(square, occupied);
    } else if constexpr (Piece == kQueen) {
        return GenerateBishopAttacks(square, occupied) | GenerateRookAttacks(square, occupied);
    } else {
        return kEmptyBoard;
    }
}

} // namespace chessengine

#endif // CHESS_ENGINE_ATTACKS_H_
