#ifndef CHESS_ENGINE_PERFT_H_
#define CHESS_ENGINE_PERFT_H_

#include <map>

#include "move.h"
#include "position.h"

namespace chessengine {

std::map<Move, std::size_t> RunPerft(std::size_t depth, Position &position);

} // namespace chessengine

#endif // CHESS_ENGINE_PERFT_H_
