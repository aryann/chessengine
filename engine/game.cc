#include "engine/game.h"

namespace follychess {

[[nodiscard]] int Game::GetRepetitionCount() const {
  const std::size_t search_depth =
      std::min<std::size_t>(history_.size(), position_.GetHalfMoves());

  int repetitions = 0;
  const std::uint64_t current_key = position_.GetKey();

  for (int i = 2; i < search_depth; i += 2) {
    const State& previous_state = history_[history_.size() - 1 - i];
    if (previous_state.key == current_key) {
      ++repetitions;
    }
  }

  return repetitions;
}

}  // namespace follychess
