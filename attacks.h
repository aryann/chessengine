#ifndef CHESS_ENGINE_ATTACKS_H_
#define CHESS_ENGINE_ATTACKS_H_

#include <array>

#include "absl/log/check.h"
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

constexpr Bitboard GetPawnAttacks(Square square, Side side) {
    static std::array<std::array<Bitboard, kNumSquares>, kNumSides> kPawnAttacks = MakePawnAttacks();
    return kPawnAttacks[side][square];
}

consteval auto GeneratePawnAttacks() {
    std::array<Bitboard, kNumSquares> attacks;
    for (int square = A8; square < kNumSquares; ++square) {
        Bitboard start(static_cast<Square>(square));
        attacks[square] = kEmptyBoard
                          | start.Shift<kNorthEast>()
                          | start.Shift<kSouthEast>()
                          | start.Shift<kSouthWest>()
                          | start.Shift<kNorthWest>();
    }
    return attacks;
}

consteval std::array<Bitboard, kNumSquares> GenerateKnightAttacks() {
    std::array<Bitboard, kNumSquares> attacks;
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
    return attacks;
}

consteval std::array<Bitboard, kNumSquares> GenerateKingAttacks() {
    std::array<Bitboard, kNumSquares> attacks;
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
    return attacks;
}

// Returns a bitboard representing a ray from the `from` square in the given
// `Direction`. The ray extends to the edge of the board, but the `from`
// square is not included.
template<Direction Direction>
consteval Bitboard MakeRay(Square from) {
    Bitboard result;
    Bitboard curr(from);
    Bitboard edge;
    while (curr) {
        curr = curr.Shift<Direction>();
        if (curr) {
            edge = curr;
        }
        result |= curr;
    }
    return result & ~edge;
}

template<Direction... Directions>
consteval Bitboard MakeRays(Square from) {
    return (MakeRay<Directions>(from) | ...);
}

template<Direction ... Directions>
consteval std::array<Bitboard, kNumSquares> MakeRelevancyMasks() {
    std::array<Bitboard, kNumSquares> result;
    for (int square = A8; square < kNumSquares; ++square) {
        result[square] = (MakeRays<Directions>(static_cast<Square>(square)) | ...);
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
    static constexpr std::array<Bitboard, kNumSquares> kBishopRelevancyMasks = MakeRelevancyMasks<
        kNorthEast, kSouthEast, kSouthWest, kNorthWest>();

    occupied &= kBishopRelevancyMasks[square];
    return GenerateSlidingAttacks<kNorthEast, kSouthEast, kSouthWest, kNorthWest>(square, occupied);
}

constexpr Bitboard GenerateRookAttacks(Square square, Bitboard occupied) {
    static constexpr std::array<Bitboard, kNumSquares> kRookRelevancyMasks = MakeRelevancyMasks<
        kNorth, kEast, kSouth, kWest>();

    occupied &= kRookRelevancyMasks[square];
    return GenerateSlidingAttacks<kNorth, kEast, kSouth, kWest>(square, occupied);
}

template<Piece Piece>
constexpr Bitboard GenerateAttacks(Square square, Bitboard occupied) {
    DCHECK(Piece != kPawn);

    if constexpr (Piece == kKnight) {
        static std::array<Bitboard, kNumSquares> kKnightAttacks = GenerateKnightAttacks();
        return kKnightAttacks[square];
    }

    if constexpr (Piece == kKing) {
        static std::array<Bitboard, kNumSquares> kKingAttacks = GenerateKingAttacks();
        return kKingAttacks[square];
    }

    if constexpr (Piece == kBishop) {
        return GenerateBishopAttacks(square, occupied);
    }

    if constexpr (Piece == kRook) {
        return GenerateRookAttacks(square, occupied);
    }

    if constexpr (Piece == kQueen) {
        return GenerateBishopAttacks(square, occupied) | GenerateRookAttacks(square, occupied);
    }

    return kEmptyBoard;
}

struct Magic {
    // Relevancy bitboard for this square and piece.
    Bitboard mask;
    std::uint64_t magic = 0;

    Bitboard *attack_tables = nullptr;
};

struct SlidingAttacks {
    std::array<Bitboard, 1> bishop_attack_tables;
    std::array<Magic, kNumSquares> bishop_magic_squares;

    std::array<Bitboard, (1 << 12) * kNumSquares> rook_attacks;
    std::array<Magic, kNumSquares> rook_magic_squares;
};

consteval SlidingAttacks MakeSlidingAttacks() {
    SlidingAttacks attacks;
    for (int square = A8; square < kNumSquares; ++square) {
        Bitboard mask = MakeRays<kNorth, kEast, kSouth, kWest>(static_cast<Square>(square));
        attacks.rook_magic_squares[square].mask = mask;
    }
    return attacks;
}

constexpr auto kSlidingAttacks = MakeSlidingAttacks();

} // namespace chessengine

#endif // CHESS_ENGINE_ATTACKS_H_
