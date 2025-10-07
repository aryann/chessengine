#include "types.h"

#include <string>

namespace chessengine {

std::string ToString(Square square) {
    int rank = 8 - square / 8;
    char file = 'a' + square % 8;
    return file + std::to_string(rank);
}

} // namespace chessengine
