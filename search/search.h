#ifndef CHESS_ENGINE_SEARCH_SEARCH_H_
#define CHESS_ENGINE_SEARCH_SEARCH_H_
#include <functional>

#include "engine/move.h"
#include "engine/position.h"

namespace chessengine {

using SearchFunc = std::function<Move(const Position&, int depth)>;

}  // namespace chessengine

#endif  // CHESS_ENGINE_SEARCH_SEARCH_H_
