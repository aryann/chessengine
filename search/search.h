#ifndef CHESS_ENGINE_SEARCH_SEARCH_H_
#define CHESS_ENGINE_SEARCH_SEARCH_H_

#include "engine/move.h"
#include "engine/position.h"

namespace chessengine {

Move Search(const Position& position, int depth);

}  // namespace chessengine

#endif  // CHESS_ENGINE_SEARCH_SEARCH_H_
