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


// MATCHER_P(Holds, inner_matcher, testing::DescribeMatcher<>(inner_matcher, negation)) {
//     if (!arg.has_value()) {
//         *result_listener << "which holds the error: " << testing::PrintToString(arg.error());
//         return false;
//     }
//
//     //return ExplainMatchResult(inner_matcher, arg.value(), result_listener);
//     const auto &value = *arg;
//     if (testing::Matches(inner_matcher)(value)) {
//         return true;
//     }
//
//     // The inner matcher failed. GTest needs to know why.
//     // We delegate the explanation to the inner matcher itself.
//     *result_listener << "which has a value that ";
//     testing::SafeMatcherCast<decltype(value)>(inner_matcher).ExplainMatchResultTo(value, *result_listener);
//     return false;
// }


MATCHER_P(IsExpectedValue, expected_value,
          std::string(negation ? "isn't" : "is") + " equal to " +
          testing::PrintToString(expected_value)) {
    if (!arg.has_value()) {
        *result_listener << "a std::expected containing error " << testing::PrintToString(arg.error());
        return false;
    }

    *result_listener << "a std::expected containing value " << testing::PrintToString(arg.value());
    return arg.value() == expected_value;
}

// Custom matcher for std::expected containing a specific error
MATCHER_P(IsExpectedError, expected_error,
          std::string(negation ? "isn't" : "is") + " equal to " +
          testing::PrintToString(expected_error)) {
    if (arg.has_value()) {
        *result_listener << "which has a value: " << testing::PrintToString(arg.value());
        return false;
    }
    return arg.error() == expected_error;
}

} // namespace chessengine

#endif // CHESS_ENGINE_TESTING_H_

