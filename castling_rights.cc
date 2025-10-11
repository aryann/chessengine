#include "castling_rights.h"

#include "types.h"

namespace chessengine {
namespace {

constexpr std::uint8_t kWhiteKingSideMask = 0b0001;
constexpr std::uint8_t kWhiteQueenSideMask = 0b0010;
constexpr std::uint8_t kBlackKingSideMask = 0b0100;
constexpr std::uint8_t kBlackQueenSideMask = 0b1000;

template<Piece Piece>
inline std::uint8_t GetMask(Side side) {
    if (side == kWhite) {
        if constexpr (Piece == kKing) {
            return kWhiteKingSideMask;
        } else {
            return kWhiteQueenSideMask;
        }
    } else {
        if constexpr (Piece == kKing) {
            return kBlackKingSideMask;
        } else {
            return kBlackQueenSideMask;
        }
    }
}

} // namespace

CastlingRights::CastlingRights():
    data_(0ULL) {
}

void CastlingRights::SetKingSide(Side side) {
    data_ |= GetMask<kKing>(side);
}

void CastlingRights::SetQueenSide(Side side) {
    data_ |= GetMask<kQueen>(side);
}

bool CastlingRights::HasKingSide(Side side) const {
    return (data_ & GetMask<kKing>(side)) != 0;
}

bool CastlingRights::HasQueenSide(Side side) const {
    return (data_ & GetMask<kQueen>(side)) != 0;
}

void CastlingRights::ClearKingSide(Side side) {
    data_ &= ~GetMask<kKing>(side);
}

void CastlingRights::ClearQueenSide(Side side) {
    data_ &= ~GetMask<kQueen>(side);
}

} // namespace chessengine
