#ifndef CHESS_ENGINE_PERFT_H_
#define CHESS_ENGINE_PERFT_H_

#include <map>

#include "move.h"
#include "position.h"

namespace chessengine {

void RunPerft(std::size_t depth, Position &position,
              std::vector<std::size_t> &depth_counts,
              std::map<Move, std::size_t> &final_move_counts);

}  // namespace chessengine

#endif  // CHESS_ENGINE_PERFT_H_
