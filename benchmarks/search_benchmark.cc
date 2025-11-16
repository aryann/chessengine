#include "benchmark/benchmark.h"
#include "engine/position.h"
#include "search/search.h"

namespace chessengine {
namespace {

template <class... Args>
void BM_Search(benchmark::State& state, Args&&... args) {
  auto args_tuple = std::make_tuple(std::move(args)...);

  int depth = state.range(0);
  auto position = Position::FromFen(std::get<0>(args_tuple));
  CHECK_EQ(position.error_or(""), "");

  for (auto _ : state) {
    Search(position.value(), SearchOptions().SetDepth(depth));
  }
}

BENCHMARK_CAPTURE(  //
    BM_Search, Starting,
    R"(rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1)")
    ->DenseRange(/* start = */ 1, /* limit = */ 6, /* step = */ 1);

BENCHMARK_CAPTURE(
    BM_Search, Position2,
    R"(r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1)")
    ->DenseRange(/* start = */ 1, /* limit = */ 5, /* step = */ 1);

}  // namespace
}  // namespace chessengine

BENCHMARK_MAIN();
