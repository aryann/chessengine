#ifndef CHESS_ENGINE_SCOPED_MOVE_H_
#define CHESS_ENGINE_SCOPED_MOVE_H_

#include "move.h"
#include "position.h"

namespace chessengine {

// A RAII class to make a move on a Position.
//
// When this object is constructed, it calls `position.Do(move)`. When it
// goes out of scope, its destructor automatically calls `position.Undo(move)`
// to restore the previous state.
class ScopedMove {
 public:
  ScopedMove(const Move &move, Position &position)
      : position_(position), undo_info_(position.Do(move)) {}

  ~ScopedMove() { position_.Undo(undo_info_); }

  ScopedMove(const ScopedMove &) = delete;

  ScopedMove &operator=(const ScopedMove &) = delete;

  ScopedMove(ScopedMove &&) = delete;

  ScopedMove &operator=(ScopedMove &&) = delete;

 private:
  Position &position_;
  UndoInfo undo_info_;
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_SCOPED_MOVE_H_
