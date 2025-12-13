#ifndef FOLLYCHESS_PERFT_H_
#define FOLLYCHESS_PERFT_H_

#include <map>

#include "move.h"
#include "position.h"

namespace follychess {

void RunPerft(std::size_t depth, const Position &position,
              std::vector<std::size_t> &final_depth_counts,
              std::map<Move, std::size_t> &final_move_counts);

}  // namespace follychess

#endif  // FOLLYCHESS_PERFT_H_
