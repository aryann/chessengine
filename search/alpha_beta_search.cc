#include "search/alpha_beta_search.h"

#include <iostream>
#include <vector>

#include "engine/move.h"
#include "engine/move_generator.h"
#include "engine/position.h"
#include "engine/scoped_move.h"
#include "engine/types.h"
#include "search/evaluation.h"
#include "search/move_ordering.h"

namespace chessengine {
namespace {

class AlphaBetaSearcher {
 public:
  AlphaBetaSearcher(const Position& position, int depth)
      : position_(position), depth_(depth), nodes_(0) {}

  [[nodiscard]] Move GetBestMove() {
    if (best_move_) {
      return *best_move_;
    }

    start_time_ = std::chrono::system_clock::now();

    constexpr static int kAlpha = -100'000;
    constexpr static int kBeta = 100'000;
    Search(kAlpha, kBeta, depth_);
    DCHECK(best_move_.has_value());

    return *best_move_;
  }

 private:
  // NOLINTNEXTLINE(misc-no-recursion)
  int Search(int alpha, int beta, int depth) {
    ++nodes_;

    MaybeLog(depth);

    if (depth == 0) {
      const int score = Evaluate(position_);
      return position_.SideToMove() == kWhite ? score : -score;
    }

    bool has_legal_moves = false;
    std::vector<Move> moves = GenerateMoves(position_);
    OrderMoves(position_, moves);

    for (Move move : moves) {
      ScopedMove scoped_move(move, position_);
      const bool is_legal = !position_.GetCheckers(~position_.SideToMove());
      if (!is_legal) {
        continue;
      }
      has_legal_moves = true;

      const int score = -Search(-beta, -alpha, depth - 1);

      if (score >= beta) {
        return beta;
      }

      if (score > alpha) {
        alpha = score;
        if (depth == depth_) {
          // Store this move as the best move if and only if this is a root
          // node.
          best_move_ = move;
        }
      }
    }

    if (!has_legal_moves) {
      if (position_.GetCheckers(position_.SideToMove())) {
        constexpr int kCheckMateScore = -20'000;
        return kCheckMateScore;
      } else {
        constexpr int kStalemateScore = 0;
        return kStalemateScore;
      }
    }

    return alpha;
  }

  constexpr void MaybeLog(int depth) {
    constexpr std::int64_t kLogFrequency = 1 << 10;
    if (nodes_ % kLogFrequency != 0) {
      return;
    }

    const auto now = std::chrono::system_clock::now();
    const std::chrono::duration<double> elapsed = now - start_time_;
    const double elapsed_seconds = elapsed.count();
    auto nodes_per_second = static_cast<std::int64_t>(nodes_ / elapsed_seconds);

    std::println(std::cout, "info depth {} nodes {} nps {}", depth_ - depth,
                 nodes_, nodes_per_second);
  }

  Position position_;
  const int depth_;
  std::optional<Move> best_move_;

  std::chrono::system_clock::time_point start_time_;
  std::int64_t nodes_;
};

}  // namespace

Move AlphaBetaSearch(const Position& position, int depth) {
  AlphaBetaSearcher searcher(position, depth);
  return searcher.GetBestMove();
}

}  // namespace chessengine
