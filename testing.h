#ifndef CHESS_ENGINE_TESTING_H_
#define CHESS_ENGINE_TESTING_H_

#include <format>
#include <gmock/gmock.h>
#include <iostream>
#include <string>

#include "absl/strings/str_split.h"
#include "absl/strings/str_cat.h"
#include "bitboard.h"

namespace chessengine {

void PrintTo(const Bitboard &bitboard, std::ostream *os);

MATCHER_P(EqualsBitboard, expected, std::format("Bitboard(0x{:x})", Bitboard(expected).Data())) {
    Bitboard expected_bitboard = Bitboard(expected);
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

