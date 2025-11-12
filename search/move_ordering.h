#ifndef CHESS_ENGINE_SEARCH_MOVE_ORDERING_H_
#define CHESS_ENGINE_SEARCH_MOVE_ORDERING_H_

#include <vector>

#include "engine/move.h"
#include "engine/position.h"

namespace chessengine {

std::vector<Move> OrderMoves(const Position& position,
                             const std::vector<Move>& moves);

}  // namespace chessengine

#endif  // CHESS_ENGINE_SEARCH_MOVE_ORDERING_H_
