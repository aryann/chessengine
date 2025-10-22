#ifndef CHESS_ENGINE_CASTLING_RIGHTS_H_
#define CHESS_ENGINE_CASTLING_RIGHTS_H_

#include <cstdint>
#include <format>

#include "types.h"

namespace chessengine {

class CastlingRights {
public:
    enum Flags : std::uint8_t {
        kNoCastlingRights = /* */ 0b0000,
        kWhiteKing = /*        */ 0b0001,
        kWhiteQueen = /*       */ 0b0010,
        kBlackKing = /*        */ 0b0100,
        kBlackQueen = /*       */ 0b1000,
    };

    CastlingRights() :
        rights_(kNoCastlingRights) {
    }

    template<Side Side>
    [[nodiscard]] constexpr bool HasKingSide() const {
        return Has<Side>(kWhiteKing);
    }

    template<Side Side>
    [[nodiscard]] constexpr bool HasQueenSide() const {
        return Has<Side>(kWhiteQueen);
    }

    constexpr void Set(Flags flags) {
        rights_ |= static_cast<std::uint8_t>(flags);
    }

    constexpr void Clear(Flags flags_to_clear) {
        rights_ &= ~static_cast<std::uint8_t>(flags_to_clear);
    }

    constexpr bool operator==(const CastlingRights &other) const = default;

    constexpr explicit operator bool() const {
        return rights_ != Flags::kNoCastlingRights;
    }

private:
    template<Side Side>
    [[nodiscard]] constexpr bool Has(Flags flags) const {
        DCHECK(Side == kWhite || Side == kBlack);
        DCHECK_EQ(kWhite, 0);
        DCHECK_EQ(kBlack, 1);

        return rights_ & (static_cast<std::uint8_t>(flags) << (Side * 2));
    }

    std::uint8_t rights_;
};

using enum CastlingRights::Flags;

} // namespace chessengine

template<>
struct std::formatter<chessengine::CastlingRights> : std::formatter<std::string> {
    static auto format(chessengine::CastlingRights rights, std::format_context &context) {
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

#endif // CHESS_ENGINE_CASTLING_RIGHTS_H_
