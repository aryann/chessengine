#include "testing.h"

#include <format>
#include <ostream>

#include "bitboard.h"

namespace chessengine {

void PrintTo(const Bitboard &bitboard, std::ostream *os) {
    *os << std::format("Bitboard(0x{:})", bitboard.Data());
}

} // namespace chessengine
