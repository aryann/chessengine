#include "search/alpha_beta_search.h"

#include <vector>

#include "engine/move.h"
#include "engine/move_generator.h"
#include "engine/position.h"
#include "engine/scoped_move.h"
#include "engine/types.h"

namespace chessengine {
namespace {}  // namespace

Move AlphaBetaSearch(const Position& position) { return Move(E2, E4); }

}  // namespace chessengine
