#ifndef CHESS_ENGINE_MOVE_GENERATOR_H_
#define CHESS_ENGINE_MOVE_GENERATOR_H_

#include <vector>

#include "move.h"
#include "position.h"
#include "types.h"

namespace follychess {

template <MoveType MoveType>
std::vector<Move> GenerateMoves(const Position &position);

std::vector<Move> GenerateMoves(const Position &position);

}  // namespace follychess

#endif  // CHESS_ENGINE_MOVE_GENERATOR_H_
