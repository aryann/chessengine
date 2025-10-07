#include "types.h"

#include <string>

namespace chessengine {

std::string ToString(Square square) {
    if (square == kNumSquares) {
        return "kNumSquares";
    }

    int rank = 8 - square / 8;
    char file = 'A' + square % 8;
    return file + std::to_string(rank);
}

} // namespace chessengine
