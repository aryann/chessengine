#ifndef CHESS_ENGINE_SCOPED_MOVE_H_
#define CHESS_ENGINE_SCOPED_MOVE_H_

#include "engine/game.h"
#include "engine/move.h"
#include "engine/position.h"

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

class ScopedMove2 {
 public:
  ScopedMove2(const Move &move, Game &game) : game_(game) { game.Do(move); }

  ~ScopedMove2() { game_.Undo(); }

  ScopedMove2(const ScopedMove2 &) = delete;

  ScopedMove2 &operator=(const ScopedMove2 &) = delete;

  ScopedMove2(ScopedMove2 &&) = delete;

  ScopedMove2 &operator=(ScopedMove2 &&) = delete;

 private:
  Game &game_;
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_SCOPED_MOVE_H_
