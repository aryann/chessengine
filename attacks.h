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
    std::array<std::array<Bitboard, kNumSquares>, kNumPieces> attacks{};

    MakeWhitePawnAttacks(attacks[kWhitePawn]);
    MakeBlackPawnAttacks(attacks[kBlackPawn]);
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
inline constexpr auto kPseudoAttacks = MakePseudoAttacks();

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
constexpr Bitboard GenerateRayAttacks(Square from, Bitboard blockers) {
    Bitboard attacks;
    Bitboard curr(from);
    while (curr) {
        curr = curr.Shift<Direction>();
        attacks |= curr;
        if (curr & blockers) {
            break;
        }
    }
    return attacks;
}

template<Direction ... Directions>
constexpr Bitboard GenerateSlidingAttacks(Square from, Bitboard blockers) {
    return (GenerateRayAttacks<Directions>(from, blockers) | ...);
}

constexpr Bitboard GenerateBishopAttacks(Square square, Bitboard blockers) {
    static std::array<Magic, kNumSquares> kBishopMagics = MakeMagic<
        kNorthEast, kSouthEast, kSouthWest, kNorthWest>();

    blockers &= kBishopMagics[square].mask;
    return GenerateSlidingAttacks<kNorthEast, kSouthEast, kSouthWest, kNorthWest>(square, blockers);
}

constexpr Bitboard GenerateRookAttacks(Square square, Bitboard blockers) {
    static std::array<Magic, kNumSquares> kRookMagics = MakeMagic<
        kNorth, kEast, kSouth, kWest>();

    blockers &= kRookMagics[square].mask;
    return GenerateSlidingAttacks<kNorth, kEast, kSouth, kWest>(square, blockers);
}

} // namespace chessengine

#endif // CHESS_ENGINE_ATTACKS_H_
