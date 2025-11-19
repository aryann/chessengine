#ifndef CHESS_ENGINE_SEARCH_SEARCH_H_
#define CHESS_ENGINE_SEARCH_SEARCH_H_

#include "engine/game.h"
#include "engine/move.h"
#include "engine/position.h"

namespace chessengine {

struct SearchOptions {
  SearchOptions& SetDepth(int depth) {
    this->depth = depth;
    return *this;
  }

  int depth = 5;

  SearchOptions& SetLogEveryN(std::int64_t log_every_n) {
    this->log_every_n = log_every_n;
    return *this;
  }

  std::int64_t log_every_n = std::numeric_limits<std::int64_t>::max();
};

Move Search(const Game& game, const SearchOptions& options = SearchOptions());

}  // namespace chessengine

#endif  // CHESS_ENGINE_SEARCH_SEARCH_H_
