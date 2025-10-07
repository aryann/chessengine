#include "move.h"

#include <ostream>

namespace chessengine {

std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << ToString(move.from()) << ToString(move.to());
    return os;
}

} // namespace chessengine
