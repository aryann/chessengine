#ifndef CHESS_ENGINE_ATTACKS_H_
#define CHESS_ENGINE_ATTACKS_H_

#include <array>
#include <random>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_join.h"
#include "bitboard.h"

namespace chessengine {

template <Direction... Directions>
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
  static std::array<std::array<Bitboard, kNumSquares>, kNumSides> kPawnAttacks =
      MakePawnAttacks();
  return kPawnAttacks[side][square];
}

consteval auto GeneratePawnAttacks() {
  std::array<Bitboard, kNumSquares> attacks;
  for (int square = A8; square < kNumSquares; ++square) {
    Bitboard start(static_cast<Square>(square));
    attacks[square] = kEmptyBoard                  //
                      | start.Shift<kNorthEast>()  //
                      | start.Shift<kSouthEast>()  //
                      | start.Shift<kSouthWest>()  //
                      | start.Shift<kNorthWest>();
  }
  return attacks;
}

consteval std::array<Bitboard, kNumSquares> GenerateKnightAttacks() {
  std::array<Bitboard, kNumSquares> attacks;
  for (int square = A8; square < kNumSquares; ++square) {
    Bitboard start(static_cast<Square>(square));
    attacks[square] = kEmptyBoard                                  //
                      | start.Shift<kNorth>().Shift<kNorthEast>()  //
                      | start.Shift<kEast>().Shift<kNorthEast>()   //
                      | start.Shift<kEast>().Shift<kSouthEast>()   //
                      | start.Shift<kSouth>().Shift<kSouthEast>()  //
                      | start.Shift<kSouth>().Shift<kSouthWest>()  //
                      | start.Shift<kWest>().Shift<kSouthWest>()   //
                      | start.Shift<kWest>().Shift<kNorthWest>()   //
                      | start.Shift<kNorth>().Shift<kNorthWest>();
  }
  return attacks;
}

consteval std::array<Bitboard, kNumSquares> GenerateKingAttacks() {
  std::array<Bitboard, kNumSquares> attacks;
  for (int square = A8; square < kNumSquares; ++square) {
    Bitboard start(static_cast<Square>(square));
    attacks[square] = kEmptyBoard                  //
                      | start.Shift<kNorth>()      //
                      | start.Shift<kNorthEast>()  //
                      | start.Shift<kEast>()       //
                      | start.Shift<kSouthEast>()  //
                      | start.Shift<kSouth>()      //
                      | start.Shift<kSouthWest>()  //
                      | start.Shift<kWest>()       //
                      | start.Shift<kNorthWest>();
  }
  return attacks;
}

// Returns a bitboard representing a ray from the `from` square in the given
// `Direction`. The ray extends to the edge of the board, but the `from`
// square is not included.
template <Direction Direction>
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

template <Direction... Directions>
constexpr Bitboard MakeRays(Square from) {
  return (MakeRay<Directions>(from) | ...);
}

template <Direction... Directions>
consteval std::array<Bitboard, kNumSquares> MakeRelevancyMasks() {
  std::array<Bitboard, kNumSquares> result;
  for (int square = A8; square < kNumSquares; ++square) {
    result[square] = (MakeRays<Directions>(static_cast<Square>(square)) | ...);
  }
  return result;
}

template <Direction Direction>
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

template <Direction... Directions>
constexpr Bitboard GenerateSlidingAttacks(Square from, Bitboard occupied) {
  return (GenerateRayAttacks<Directions>(from, occupied) | ...);
}

constexpr Bitboard GenerateBishopAttacks(Square square, Bitboard occupied) {
  static constexpr std::array<Bitboard, kNumSquares> kBishopRelevancyMasks =
      MakeRelevancyMasks<kNorthEast, kSouthEast, kSouthWest, kNorthWest>();

  occupied &= kBishopRelevancyMasks[square];
  return GenerateSlidingAttacks<kNorthEast, kSouthEast, kSouthWest, kNorthWest>(
      square, occupied);
}

constexpr Bitboard GenerateRookAttacks(Square square, Bitboard occupied) {
  static constexpr std::array<Bitboard, kNumSquares> kRookRelevancyMasks =
      MakeRelevancyMasks<kNorth, kEast, kSouth, kWest>();

  occupied &= kRookRelevancyMasks[square];
  return GenerateSlidingAttacks<kNorth, kEast, kSouth, kWest>(square, occupied);
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

// Holds the magic bitboard data for a single square and piece type
// (bishop or rook).
struct MagicEntry {
  // The mask of relevant squares for this piece and square.
  Bitboard mask;

  std::uint64_t magic;
  std::uint8_t shift;

  // Pointer to the start of this square's attack table.
  Bitboard *attack_table;
};

struct SlidingAttackTables {
  // The following diagram shows the number of relevancy squares for bishop
  // attacks:
  //
  //   8: 6 5 5 5 5 5 5 6
  //   7: 5 5 5 5 5 5 5 5
  //   6: 5 5 7 7 7 7 5 5
  //   5: 5 5 7 9 9 7 5 5
  //   4: 5 5 7 9 9 7 5 5
  //   3: 5 5 7 7 7 7 5 5
  //   2: 5 5 5 5 5 5 5 5
  //   1: 6 5 5 5 5 5 5 6
  //      a b c d e f g h
  //
  // For simplicity, the bishop attack table allocates kNumSquares * 2^9.
  static constexpr int kBishopMaxRelevancyBits = 9;
  static constexpr int kBishopTableSize =
      kNumSquares * (1 << kBishopMaxRelevancyBits);
  std::array<Bitboard, kBishopTableSize> bishop_attacks;

  std::array<MagicEntry, kNumSquares> bishop_magic_squares;

  // Unlike the bishop attack table, the number of relevancy squares for a rook
  // is the same for every square.
  static constexpr int kRookMaxRelevancyBits = 12;
  static constexpr int kRookTableSizeBits =
      kNumSquares * (1 << kRookMaxRelevancyBits);
  std::array<Bitboard, kRookTableSizeBits> rook_attacks;

  std::array<MagicEntry, kNumSquares> rook_magic_squares;
};

template <Direction... Directions>
constexpr void FindMagicForSquare(Square from, Bitboard *attack_table,
                                  MagicEntry &magic_struct) {
  Bitboard mask = MakeRays<Directions...>(from);
  std::vector<Bitboard> occupancies = MakePowerSet(mask);
  std::uint8_t shift = 64 - mask.GetCount();

  std::vector<Bitboard> attacks;
  attacks.reserve(occupancies.size());
  for (Bitboard occupancy : occupancies) {
    attacks.push_back(GenerateSlidingAttacks<Directions...>(from, occupancy));
  }

  static std::mt19937 kEngine(std::random_device{}());
  std::uniform_int_distribution<std::uint64_t> dist(0);

  while (true) {
    // Generate a "sparse" magic number candidate. ANDing three random numbers
    // reduces the bit density to ~1/8.
    //
    // This heuristic is known to produce "good" magic numbers (those
    // that minimize collisions) much faster than fully random numbers.
    std::uint64_t magic = dist(kEngine) & dist(kEngine) & dist(kEngine);

    std::vector<Bitboard> placements(attacks.size(), Bitboard(0));
    bool found = true;

    for (int i = 0; i < occupancies.size(); ++i) {
      std::uint64_t index = (magic * occupancies[i].Data()) >> shift;

      if (placements[index]) {
        found = false;
        break;
      }
      placements[index] = attacks[i];
    }

    if (found) {
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

constexpr SlidingAttackTables GenerateSlidingAttackTables() {
  SlidingAttackTables sliding_attacks;
  Bitboard *bishop_attack_table = sliding_attacks.bishop_attacks.begin();
  Bitboard *rook_attack_table = sliding_attacks.rook_attacks.begin();

  for (int square = A8; square < kNumSquares; ++square) {
    Square from = static_cast<Square>(square);

    // Generate the MagicEntry for a bishop on this square:
    FindMagicForSquare<kNorthEast, kSouthEast, kSouthWest, kNorthWest>(
        from, bishop_attack_table + (1 << 9) * from,
        sliding_attacks.bishop_magic_squares[square]);

    // Generate the MagicEntry for a rook on this square:
    FindMagicForSquare<kNorth, kEast, kSouth, kWest>(
        from, rook_attack_table + (1 << 12) * from,
        sliding_attacks.rook_magic_squares[square]);
  }
  return sliding_attacks;
}

const auto kSlidingAttackTables = GenerateSlidingAttackTables();

[[nodiscard]] constexpr Bitboard GenerateBishopAttacksFast(Square square,
                                                           Bitboard occupied) {
  const MagicEntry &magic = kSlidingAttackTables.bishop_magic_squares[square];
  occupied &= magic.mask;
  std::uint64_t index = (magic.magic * occupied.Data()) >> magic.shift;
  return magic.attack_table[index];
}

[[nodiscard]] constexpr Bitboard GenerateRookAttacksFast(Square square,
                                                         Bitboard occupied) {
  const MagicEntry &magic = kSlidingAttackTables.rook_magic_squares[square];
  occupied &= magic.mask;
  std::uint64_t index = (magic.magic * occupied.Data()) >> magic.shift;
  return magic.attack_table[index];
}

template <Piece Piece>
[[nodiscard]] constexpr Bitboard GenerateAttacks(Square square,
                                                 Bitboard occupied) {
  static_assert(Piece != kPawn);

  if constexpr (Piece == kKnight) {
    static std::array<Bitboard, kNumSquares> kKnightAttacks =
        GenerateKnightAttacks();
    return kKnightAttacks[square];
  }

  if constexpr (Piece == kKing) {
    static std::array<Bitboard, kNumSquares> kKingAttacks =
        GenerateKingAttacks();
    return kKingAttacks[square];
  }

  if constexpr (Piece == kBishop) {
    return GenerateBishopAttacksFast(square, occupied);
  }

  if constexpr (Piece == kRook) {
    return GenerateRookAttacksFast(square, occupied);
  }

  if constexpr (Piece == kQueen) {
    return GenerateBishopAttacksFast(square, occupied) |
           GenerateRookAttacksFast(square, occupied);
  }

  return kEmptyBoard;
}

}  // namespace chessengine

#endif  // CHESS_ENGINE_ATTACKS_H_
