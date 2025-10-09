#include "move.h"

#include <ostream>

namespace chessengine {

std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << "Move(";
    os << ToString(move.from()) << ", " << ToString(move.to());
    os << ")";
    return os;
}

} // namespace chessengine
