#include "search/search.h"

#include <iostream>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "engine/move.h"
#include "engine/move_generator.h"
#include "engine/position.h"
#include "engine/scoped_move.h"
#include "engine/types.h"
#include "search/evaluation.h"
#include "search/move_ordering.h"

namespace chessengine {
namespace {

enum BoundType : std::int8_t {
  Exact,
  UpperBound,
  LowerBound,
};

struct Transposition {
  int depth = 0;
  int score = 0;
  BoundType type = Exact;
};

class AlphaBetaSearcher {
 public:
  AlphaBetaSearcher(const Position& position, const SearchOptions& options)
      : position_(position),
        requested_search_depth_(options.depth),
        log_every_n_(options.log_every_n),
        nodes_(0),
        transposition_hits_(0) {}

  [[nodiscard]] Move GetBestMove() {
    if (best_move_) {
      return *best_move_;
    }

    start_time_ = std::chrono::system_clock::now();

    constexpr static int kAlpha = -100'000;
    constexpr static int kBeta = 100'000;
    Search(kAlpha, kBeta, 0);
    DCHECK(best_move_.has_value());

    return *best_move_;
  }

 private:
  // NOLINTNEXTLINE(misc-no-recursion)
  int Search(int alpha, const int beta, const int depth) {
    ++nodes_;
    MaybeLog(depth);

    if (std::optional<int> score = ProbeTranspositions(alpha, beta, depth)) {
      ++transposition_hits_;
      return *score;
    }

    if (depth == requested_search_depth_) {
      int score = QuiescentSearch(alpha, beta, 1);
      transpositions_[position_.GetKey()] = {
          .depth = depth,
          .score = score,
          .type = Exact,
      };
      return score;
    }

    bool has_legal_moves = false;
    std::vector<Move> moves = GenerateMoves(position_);
    OrderMoves(position_, moves);

    BoundType transposition_type = UpperBound;
    for (Move move : moves) {
      ScopedMove scoped_move(move, position_);
      const bool is_legal = !position_.GetCheckers(~position_.SideToMove());
      if (!is_legal) {
        continue;
      }
      has_legal_moves = true;

      const int score = -Search(-beta, -alpha, depth + 1);

      if (score >= beta) {
        transpositions_[position_.GetKey()] = {
            .depth = depth,
            .score = score,
            .type = LowerBound,
        };
        return beta;
      }

      if (score > alpha) {
        alpha = score;
        transposition_type = Exact;
        if (depth == 0) {
          // Store this move as the best move if and only if this is a root
          // node.
          best_move_ = move;
        }
      }
    }

    if (has_legal_moves) {
      transpositions_[position_.GetKey()] = {
          .depth = depth,
          .score = alpha,
          .type = transposition_type,
      };
      return alpha;
    }

    const bool is_checkmate = position_.GetCheckers(position_.SideToMove());
    if (is_checkmate) {
      constexpr int kBaseCheckMateScore = -20'000;

      // Favor checkmates closer to the root of the tree.
      return kBaseCheckMateScore + depth;
    }

    constexpr int kStalemateScore = 0;
    return kStalemateScore;
  }

  // NOLINTNEXTLINE(misc-no-recursion)
  [[nodiscard]] int QuiescentSearch(int alpha, const int beta,
                                    const int depth) {
    ++nodes_;
    MaybeLog(requested_search_depth_, depth);

    int score = GetScore();
    if (score >= beta) {
      return beta;
    }
    alpha = std::max(alpha, score);

    std::vector<Move> moves = GenerateMoves<kCapture>(position_);
    OrderMoves(position_, moves);
    for (Move move : moves) {
      ScopedMove scoped_move(move, position_);
      const bool is_legal = !position_.GetCheckers(~position_.SideToMove());
      if (!is_legal) {
        continue;
      }

      score = -QuiescentSearch(-beta, -alpha, depth + 1);

      if (score >= beta) {
        return beta;
      }
      alpha = std::max(alpha, score);
    }

    return alpha;
  }

  [[nodiscard]] int GetScore() const {
    const int score = Evaluate(position_);
    return position_.SideToMove() == kWhite ? score : -score;
  }

  constexpr void MaybeLog(const int depth,
                          const int additional_depth = 0) const {
    if (nodes_ % log_every_n_ != 0) {
      return;
    }

    const auto now = std::chrono::system_clock::now();
    const std::chrono::duration<double> elapsed = now - start_time_;
    const double elapsed_seconds = elapsed.count();
    auto nodes_per_second = static_cast<std::int64_t>(nodes_ / elapsed_seconds);

    const int selective_depth = depth + additional_depth;

    std::println(
        std::cout, "info depth {} seldepth {} nodes {} nps {} tbhits {}", depth,
        selective_depth, nodes_, nodes_per_second, transposition_hits_);
  }

  [[nodiscard]] std::optional<int> ProbeTranspositions(const int alpha,
                                                       const int beta,
                                                       const int depth) const {
    auto it = transpositions_.find(position_.GetKey());
    if (it == transpositions_.end()) {
      return std::nullopt;
    }

    const Transposition& transposition = it->second;
    if (transposition.depth < depth) {
      return std::nullopt;
    }

    switch (transposition.type) {
      case Exact:
        return transposition.score;
      case UpperBound:
        if (transposition.score <= alpha) {
          return alpha;
        }
      case LowerBound:
        if (transposition.score >= beta) {
          return beta;
        }
      default:
        return std::nullopt;
    }
  }

  Position position_;

  const int requested_search_depth_;
  const std::int64_t log_every_n_;

  std::optional<Move> best_move_;

  std::chrono::system_clock::time_point start_time_;
  std::int64_t nodes_;
  std::int64_t transposition_hits_;

  absl::flat_hash_map<std::uint64_t, Transposition> transpositions_;
};

}  // namespace

Move Search(const Position& position, const SearchOptions& options) {
  AlphaBetaSearcher searcher(position, options);
  return searcher.GetBestMove();
}

}  // namespace chessengine
