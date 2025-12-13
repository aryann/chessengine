#ifndef CHESS_ENGINE_SEARCH_MOVE_ORDERING_H_
#define CHESS_ENGINE_SEARCH_MOVE_ORDERING_H_

#include <vector>

#include "engine/move.h"
#include "engine/position.h"

namespace follychess {

void OrderMoves(const Position& position, std::vector<Move>& moves);

}  // namespace follychess

#endif  // CHESS_ENGINE_SEARCH_MOVE_ORDERING_H_
