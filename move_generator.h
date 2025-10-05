#ifndef CHESS_ENGINE_MOVE_GENERATOR_H_
#define CHESS_ENGINE_MOVE_GENERATOR_H_

#include <cstdint>
#include <vector>

#include "move.h"
#include "position.h"
#include "types.h"

namespace chessengine {

template<MoveType MoveType>
std::vector<Move> GenerateMoves(const Position& position);

} // namespace chessengine

#endif // CHESS_ENGINE_MOVE_GENERATOR_H_
