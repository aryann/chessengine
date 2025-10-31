#ifndef CHESS_ENGINE_ATTACKS_H_
#define CHESS_ENGINE_ATTACKS_H_

#include <array>
#include <random>
#include "absl/strings/str_join.h"


#include "absl/log/log.h"
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
constexpr Bitboard MakeRay(Square from) {
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
constexpr Bitboard MakeRays(Square from) {
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
    static_assert(Piece != kPawn);

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

constexpr std::vector<Bitboard> MakePowerSet(Bitboard mask) {
    // https://www.chessprogramming.org/Traversing_Subsets_of_a_Set
    const std::size_t cardinality = 1ULL << mask.GetCount();
    std::vector<Bitboard> subsets(cardinality);

    Bitboard sub_mask;
    for (int i = 0; i < cardinality; ++i) {
        subsets[i] = sub_mask;
        sub_mask = (sub_mask - mask) & mask;
    }

    return subsets;
}

struct Magic {
    // Relevancy bitboard for this square and piece.
    Bitboard mask;
    std::uint64_t magic;
    std::uint8_t shift;

    Bitboard *attack_table;
};

struct SlidingAttacks {
    std::array<Bitboard, 1> bishop_attack_tables;
    std::array<Magic, kNumSquares> bishop_magic_squares;

    std::array<Bitboard, (1 << 12) * kNumSquares> rook_attacks;
    std::array<Magic, kNumSquares> rook_magic_squares;
};

template<Direction ... Directions>
constexpr void MakeSlidingAttacks(Square from, Bitboard &attack_table1, Magic &magic_struct) {
    Bitboard mask = MakeRays<Directions...>(from);
    std::vector<Bitboard> occupancies = MakePowerSet(mask);

    std::vector<Bitboard> attacks;
    attacks.reserve(occupancies.size());
    for (Bitboard occupancy: occupancies) {
        attacks.push_back(GenerateSlidingAttacks<Directions...>(from, occupancy));
    }

    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<std::uint64_t> dist(0);
    while (true) {
        std::uint64_t magic = dist(engine) & dist(engine) & dist(engine);
        std::vector<Bitboard> placements(attacks.size(), Bitboard(0));
        std::uint8_t shift = 64 - mask.GetCount();
        bool found = true;
        int attempts = 0;

        for (int i = 0; i < occupancies.size(); ++i) {
            std::uint64_t index = (magic * occupancies[i].Data()) >> shift;

            if (placements[index]) {
                ++attempts;
                found = false;
                break;
            }
            placements[index] = attacks[i];
        }

        if (found) {
            LOG(INFO) << "Found rook magic for " << ToString(from) << " after " << attempts << " attempt(s).";

            Bitboard *attack_table = &attack_table1 + (1 << 12) * from;
            for (int i = 0; i < placements.size(); ++i) {
                attack_table[i] = placements[i];
            }

            magic_struct = {
                    .mask = mask,
                    .shift = shift,
                    .magic = magic,
                    .attack_table = attack_table,
            };
            break;
        }

    }
}

constexpr SlidingAttacks MakeSlidingAttacks() {
    SlidingAttacks sliding_attacks;
    for (int square = A8; square < kNumSquares; ++square) {
        Square from = static_cast<Square>(square);

        MakeSlidingAttacks<kNorth, kEast, kSouth, kWest>(
                from,
                *sliding_attacks.rook_attacks.begin(),
                sliding_attacks.rook_magic_squares[square]);
    }
    return sliding_attacks;
}

const auto kSlidingAttacks = MakeSlidingAttacks();

constexpr Bitboard GenerateRookAttacksFast(Square square, Bitboard occupied) {
    const Magic &magic = kSlidingAttacks.rook_magic_squares[square];
    std::uint64_t index = (magic.magic * occupied.Data()) >> magic.shift;
    return magic.attack_table[index];
}

} // namespace chessengine

#endif // CHESS_ENGINE_ATTACKS_H_
