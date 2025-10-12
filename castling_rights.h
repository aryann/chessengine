#ifndef CHESS_ENGINE_CASTLING_RIGHTS_H_
#define CHESS_ENGINE_CASTLING_RIGHTS_H_

#include <cstdint>
#include <format>

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

    constexpr bool operator==(const CastlingRights &other) const = default;

    constexpr explicit operator bool() const {
        return data_ != 0;
    }

private:
    std::uint8_t data_;
};

} // namespace chessengine

template<>
struct std::formatter<chessengine::CastlingRights> : std::formatter<std::string> {
    static auto format(chessengine::CastlingRights rights, std::format_context &context) {
        auto out = context.out();
        if (!rights) {
            return std::format_to(out, "-");
        }

        using chessengine::kWhite;
        using chessengine::kBlack;

        std::format_to(out, "{}", rights.HasKingSide(kWhite) ? "K" : "");
        std::format_to(out, "{}", rights.HasQueenSide(kWhite) ? "Q" : "");
        std::format_to(out, "{}", rights.HasKingSide(kBlack) ? "k" : "");
        std::format_to(out, "{}", rights.HasQueenSide(kBlack) ? "q" : "");
        return out;
    }
};

#endif // CHESS_ENGINE_CASTLING_RIGHTS_H_
