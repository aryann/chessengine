#ifndef CHESS_ENGINE_SEARCH_EVALUATION_H_
#define CHESS_ENGINE_SEARCH_EVALUATION_H_

#include "engine/position.h"

namespace chessengine {

[[nodiscard]] int GetMaterialScore(const Position& position);

[[nodiscard]] int GetPlacementScore(const Position& position);

[[nodiscard]] int Evaluate(const Position& position);

}  // namespace chessengine

#endif  // CHESS_ENGINE_SEARCH_EVALUATION_H_
