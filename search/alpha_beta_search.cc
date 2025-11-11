#include "search/alpha_beta_search.h"

#include <iostream>
#include <vector>

#include "engine/move.h"
#include "engine/move_generator.h"
#include "engine/position.h"
#include "engine/scoped_move.h"
#include "engine/types.h"
#include "search/evaluation.h"

namespace chessengine {
namespace {

class AlphaBetaSearcher {
 public:
  AlphaBetaSearcher(const Position& position, int depth)
      : position_(position), depth_(depth) {}

  [[nodiscard]] Move GetBestMove() {
    if (best_move_) {
      return *best_move_;
    }

    constexpr static int kInitialAlpha = std::numeric_limits<int>::min();
    constexpr static int kInitialBeta = std::numeric_limits<int>::max();
    Search(kInitialAlpha, kInitialBeta, depth_);
    DCHECK(best_move_.has_value());

    return *best_move_;
  }

 private:
  // NOLINTNEXTLINE(misc-no-recursion)
  int Search(int alpha, int beta, int depth) {
    if (depth == 0) {
      int score = GetMaterialScore(position_);
      return position_.SideToMove() == kWhite ? score : -score;
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

      int score = -Search(-beta, -alpha, depth - 1);

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

  Position position_;
  int depth_;
  std::optional<Move> best_move_;
};

}  // namespace

Move AlphaBetaSearch(const Position& position, int depth) {
  AlphaBetaSearcher searcher(position, depth);
  return searcher.GetBestMove();
}

}  // namespace chessengine
