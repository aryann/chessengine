#ifndef CHESS_ENGINE_TESTING_H_
#define CHESS_ENGINE_TESTING_H_

#include <format>
#include <gmock/gmock.h>
#include <iostream>
#include <string>

#include "absl/strings/str_split.h"
#include "absl/strings/str_cat.h"
#include "bitboard.h"
#include "position.h"

namespace chessengine {

void PrintTo(const Bitboard &bitboard, std::ostream *os);

MATCHER_P(EqualsBitboard, expected, std::format("Bitboard(0x{:x})", Bitboard(expected).Data())) {
    Bitboard expected_bitboard = Bitboard(expected);
    Bitboard actual_bitboard = arg;
    if (actual_bitboard == expected_bitboard) {
        return true;
    }

    std::vector<std::string> expected_parts =
            absl::StrSplit(std::format("{}", expected_bitboard), '\n');
    std::vector<std::string> actual_parts =
            absl::StrSplit(std::format("{}", actual_bitboard), '\n');

    *result_listener
            << "\n\n"
            << "      Expected:                Actual:\n"
            << "      ---------                -------";

    for (int i = 0; i < expected_parts.size(); ++i) {
        *result_listener << '\n' << expected_parts[i] << "      " << actual_parts[i];
    }

    return false;
}

std::string TestPositionToFen(std::string_view input);

MATCHER_P(EqualsPosition, expected, "") {
    std::string fen = TestPositionToFen(expected);
    auto result = Position::FromFen(fen);
    if (!result.has_value()) {
        *result_listener << "Could not parse position: " << result.error();
        return false;
    }

    const Position &expected_position = result.value();
    const Position &actual_position = arg;

    if (expected_position == actual_position) {
        return true;
    }

    std::vector<std::string> expected_parts =
            absl::StrSplit(std::format("{}", expected_position), '\n');
    std::vector<std::string> actual_parts =
            absl::StrSplit(std::format("{}", actual_position), '\n');

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

