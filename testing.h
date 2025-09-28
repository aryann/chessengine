#ifndef CHESS_ENGINE_TESTING_H_
#define CHESS_ENGINE_TESTING_H_

#include <format>
#include <gmock/gmock.h>
#include <iostream>
#include <string>

#include "absl/strings/str_split.h"
#include "absl/strings/str_cat.h"

namespace chessengine {

static constexpr Bitboard FromString(std::string_view input) {
    Bitboard bitboard = kEmptyBoard;
    int rank = 7;
    int file = 0;

    int i = 0;
    while (i < input.size()) {
        const char curr = input[i];
        ++i;

        if (curr != '.' && curr != 'X') {
            continue;
        }

        if (curr == 'X') {
            auto square = static_cast<Square>(rank * 8 + file);
            bitboard |= Set(bitboard, square);
        }

        ++file;
        if (file == 8) {
            --rank;
            file = 0;
        }
    }

    return bitboard;
}

MATCHER_P(EqualsBitboard, expected, absl::StrCat(FromString(expected))) {
    Bitboard expected_bitboard = FromString(expected);
    if (arg == expected_bitboard) {
        return true;
    }

    std::vector<std::string> expected_parts = absl::StrSplit(std::format("{}", expected_bitboard), '\n');
    std::vector<std::string> actual_parts = absl::StrSplit(std::format("{}", arg), '\n');

    *result_listener
            << "\n\n"
            << "      Expected:                Actual:\n"
            << "      ---------                -------";

    for (int i = 0; i < expected_parts.size(); ++i) {
        *result_listener << '\n' << expected_parts[i] << "      " << actual_parts[i];
    }

    return false;
}

} // namespace chessengine

#endif // CHESS_ENGINE_TESTING_H_

