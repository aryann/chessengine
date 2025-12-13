#ifndef FOLLYCHESS_SEARCH_EVALUATION_H_
#define FOLLYCHESS_SEARCH_EVALUATION_H_

#include "engine/position.h"

namespace follychess {

[[nodiscard]] int GetMaterialScore(const Position& position);

[[nodiscard]] int GetPlacementScore(const Position& position);

[[nodiscard]] int Evaluate(const Position& position);

}  // namespace follychess

#endif  // FOLLYCHESS_SEARCH_EVALUATION_H_
