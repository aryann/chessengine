#ifndef CHESS_ENGINE_CASTLING_RIGHTS_H_
#define CHESS_ENGINE_CASTLING_RIGHTS_H_

#include <cstdint>

#include "types.h"

namespace chessengine {

class CastlingRights {
public:
    CastlingRights();

    void SetKingSide(Side side);

    void SetQueenSide(Side side);

    [[nodiscard]] bool HasKingSide(Side side) const;

    [[nodiscard]] bool HasQueenSide(Side side) const;

    void ClearKingSide(Side side);

    void ClearQueenSide(Side side);

private:
    std::uint8_t data_;
};

} // namespace chessengine

#endif // CHESS_ENGINE_CASTLING_RIGHTS_H_
