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

    constexpr static int kInitialAlpha = std::numeric_limits<int>::min();
    constexpr static int kInitialBeta = std::numeric_limits<int>::max();
    Search(kInitialAlpha, kInitialBeta, depth_);
    DCHECK(best_move_.has_value());

    return *best_move_;
  }

 private:
  // NOLINTNEXTLINE(misc-no-recursion)
  int Search(int alpha, int beta, int depth) {
    ++nodes_;

    MaybeLog(depth);

    if (depth == 0) {
      return Evaluate(position_);
    }

    int best_score = std::numeric_limits<int>::min();
    bool has_legal_moves = false;
    for (Move move : GenerateMoves(position_)) {
      ScopedMove scoped_move(move, position_);
      if (position_.GetCheckers(~position_.SideToMove())) {
        // This move is not legal.
        continue;
      }
      has_legal_moves = true;

      int score = Search(-beta, -alpha, depth - 1);

      if (score > best_score) {
        // Found a better move.
        best_score = score;

        if (score > alpha) {
          alpha = score;
          if (depth_ == depth) {
            // Save the best move if and only if this is the root.
            best_move_ = move;
          }
        }
      }

      if (score >= beta) {
        return best_score;
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

    return best_score;
  }

  constexpr void MaybeLog(int depth) {
    constexpr std::int64_t kLogFrequency = 1 << 16;
    if (nodes_ % kLogFrequency != 0) {
      return;
    }

    const auto now = std::chrono::system_clock::now();
    const std::chrono::duration<double> elapsed = now - start_time_;
    const double elapsed_seconds = elapsed.count();
    int nodes_per_second = static_cast<int>(nodes_ / elapsed_seconds);

    std::println(std::cout, "info depth {} nodes {} nps {}", depth, nodes_,
                 nodes_per_second);
  }

  Position position_;
  const int depth_;
  std::optional<Move> best_move_;

  std::chrono::system_clock::time_point start_time_;
  int nodes_;
};

}  // namespace

Move AlphaBetaSearch(const Position& position, int depth) {
  AlphaBetaSearcher searcher(position, depth);
  return searcher.GetBestMove();
}

}  // namespace chessengine
