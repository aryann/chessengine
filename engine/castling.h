#ifndef CHESS_ENGINE_CASTLING_RIGHTS_H_
#define CHESS_ENGINE_CASTLING_RIGHTS_H_

#include <format>

#include "bitboard.h"
#include "types.h"

namespace chessengine {

template <Side Side>
constexpr Bitboard GetKingSideCastlingPath() {
  static_assert(Side == kWhite || Side == kBlack);

  if constexpr (Side == kWhite) {
    return Bitboard(F1) | Bitboard(G1);
  } else {
    return Bitboard(F8) | Bitboard(G8);
  }
}

template <Side Side>
constexpr Bitboard GetQueenSideCastlingPath() {
  static_assert(Side == kWhite || Side == kBlack);

  if constexpr (Side == kWhite) {
    return Bitboard(B1) | Bitboard(C1) | Bitboard(D1);
  } else {
    return Bitboard(B8) | Bitboard(C8) | Bitboard(D8);
  }
}

class CastlingRights {
 public:
  enum Flags : std::uint8_t {
    kNoCastlingRights = /* */ 0b0000,
    kWhiteKing = /*        */ 0b0001,
    kWhiteQueen = /*       */ 0b0010,
    kBlackKing = /*        */ 0b0100,
    kBlackQueen = /*       */ 0b1000,
    kAllCastlingRights = /**/ 0b1111,
  };

  explicit CastlingRights(std::uint8_t rights = kNoCastlingRights)
      : rights_(rights) {}

  template <Side Side>
  [[nodiscard]] constexpr bool HasKingSide() const {
    static_assert(Side == kWhite || Side == kBlack);

    if constexpr (Side == kWhite) {
      return rights_ & kWhiteKing;
    } else {
      return rights_ & kBlackKing;
    }
  }

  template <Side Side>
  [[nodiscard]] constexpr bool HasQueenSide() const {
    static_assert(Side == kWhite || Side == kBlack);

    if constexpr (Side == kWhite) {
      return rights_ & kWhiteQueen;
    } else {
      return rights_ & kBlackQueen;
    }
  }

  constexpr void InvalidateOnMove(Square square) {
    static constexpr std::array<std::uint8_t, kNumSquares> kCastlingMasks = [] {
      std::array<std::uint8_t, kNumSquares> masks{};
      masks.fill(0b1111);

      // White masks:
      masks[A1] = ~kWhiteQueen;
      masks[E1] = ~(kWhiteKing | kWhiteQueen);
      masks[H1] = ~kWhiteKing;

      // Black masks:
      masks[A8] = ~kBlackQueen;
      masks[E8] = ~(kBlackKing | kBlackQueen);
      masks[H8] = ~kBlackKing;

      return masks;
    }();

    rights_ &= kCastlingMasks[square];
  }

  constexpr void Set(Flags flags) {
    rights_ |= static_cast<std::uint8_t>(flags);
  }

  constexpr bool operator==(const CastlingRights &other) const = default;

  constexpr explicit operator bool() const {
    return rights_ != Flags::kNoCastlingRights;
  }

 private:
  std::uint8_t rights_;
};

using enum CastlingRights::Flags;

}  // namespace chessengine

template <>
struct std::formatter<chessengine::CastlingRights>
    : std::formatter<std::string> {
  static auto format(chessengine::CastlingRights rights,
                     std::format_context &context) {
    auto out = context.out();
    if (!rights) {
      return std::format_to(out, "-");
    }

    using enum chessengine::Side;

    std::format_to(out, "{}", rights.HasKingSide<kWhite>() ? "K" : "");
    std::format_to(out, "{}", rights.HasQueenSide<kWhite>() ? "Q" : "");
    std::format_to(out, "{}", rights.HasKingSide<kBlack>() ? "k" : "");
    std::format_to(out, "{}", rights.HasQueenSide<kBlack>() ? "q" : "");
    return out;
  }
};

#endif  // CHESS_ENGINE_CASTLING_RIGHTS_H_
