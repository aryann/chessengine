#ifndef CHESS_ENGINE_TESTING_H_
#define CHESS_ENGINE_TESTING_H_

#include <format>
#include <string>
#include <gmock/gmock.h>

#include "absl/strings/str_split.h"

namespace chessengine {

MATCHER_P(MatchesBitboard, expected, "") {
    if (arg == expected) {
        return true;
    }

    std::vector<std::string> expected_parts = absl::StrSplit(std::format("{}", expected), '\n');
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
