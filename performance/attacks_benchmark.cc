#include "attacks.h"
#include "benchmark/benchmark.h"
#include "types.h"

namespace chessengine {
namespace {

[[nodiscard]] Bitboard GenerateBishopAttacksOnTheFly(Square square,
                                                     Bitboard occupied) {
  occupied &= kSlidingAttackTables.bishop_magic_squares[square].mask;
  return GenerateSlidingAttacks<kNorthEast, kSouthEast, kSouthWest, kNorthWest>(
      square, occupied);
}

[[nodiscard]] Bitboard GenerateRookAttacksOnTheFly(Square square,
                                                   Bitboard occupied) {
  occupied &= kSlidingAttackTables.rook_magic_squares[square].mask;
  return GenerateSlidingAttacks<kNorth, kEast, kSouth, kWest>(square, occupied);
}

[[nodiscard]] Bitboard GenerateQueenAttacksOnTheFly(Square square,
                                                    Bitboard occupied) {
  return GenerateBishopAttacksOnTheFly(square, occupied) |
         GenerateRookAttacksOnTheFly(square, occupied);
}

template <Piece Piece>
[[nodiscard]] Bitboard GenerateAttacksOnTheFly(Square square,
                                               Bitboard occupied) {
  static_assert(Piece == kBishop || Piece == kRook || Piece == kQueen);

  if constexpr (Piece == kBishop) {
    return GenerateBishopAttacksOnTheFly(square, occupied);
  }
  if constexpr (Piece == kRook) {
    return GenerateRookAttacksOnTheFly(square, occupied);
  }
  return GenerateQueenAttacksOnTheFly(square, occupied);
}

template <Piece Piece>
void BM_GenerateAttacksOnTheFly(benchmark::State& state) {
  std::mt19937 engine(std::random_device{}());
  std::uniform_int_distribution<std::uint64_t> dist(0);

  for (auto _ : state) {
    Square square = static_cast<Square>(dist(engine) % kNumSquares);
    Bitboard occupied(dist(engine));
    benchmark::DoNotOptimize(GenerateAttacksOnTheFly<Piece>(square, occupied));
  }
}

template <Piece Piece>
void BM_LookupAttacks(benchmark::State& state) {
  static_assert(Piece == kBishop || Piece == kRook || Piece == kQueen);

  std::mt19937 engine(std::random_device{}());
  std::uniform_int_distribution<std::uint64_t> dist(0);

  for (auto _ : state) {
    Square square = static_cast<Square>(dist(engine) % kNumSquares);
    Bitboard occupied(dist(engine));
    benchmark::DoNotOptimize(GenerateAttacks<Piece>(square, occupied));
  }
}

// Naively generate attacks on the fly:
BENCHMARK(BM_GenerateAttacksOnTheFly<kBishop>);
BENCHMARK(BM_GenerateAttacksOnTheFly<kRook>);
BENCHMARK(BM_GenerateAttacksOnTheFly<kQueen>);

// Use magic bitboard to lookup precomputed attacks:
BENCHMARK(BM_LookupAttacks<kBishop>);
BENCHMARK(BM_LookupAttacks<kRook>);
BENCHMARK(BM_LookupAttacks<kQueen>);

}  // namespace
}  // namespace chessengine

BENCHMARK_MAIN();
