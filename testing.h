#ifndef CHESS_ENGINE_TESTING_H_
#define CHESS_ENGINE_TESTING_H_

#include <gmock/gmock.h>

#include <format>
#include <iostream>
#include <source_location>
#include <string>
#include <variant>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "bitboard.h"
#include "position.h"

namespace chessengine {

std::expected<Position, std::string> TryMakePosition(std::string_view input);

Position MakePosition(
    std::string_view input,
    std::source_location location = std::source_location::current());

Move MakeMove(std::string_view input,
              std::source_location location = std::source_location::current());

std::vector<Move> MakeMoves(
    std::initializer_list<std::string_view> input,
    std::source_location location = std::source_location::current());

void PrintTo(const Bitboard &bitboard, std::ostream *os);

MATCHER_P(EqualsBitboard, expected,
          std::format("Bitboard(0x{:x})", Bitboard(expected).Data())) {
  Bitboard expected_bitboard = Bitboard(expected);
  Bitboard actual_bitboard = arg;
  if (actual_bitboard == expected_bitboard) {
    return true;
  }

  std::vector<std::string> expected_parts =
      absl::StrSplit(std::format("{}", expected_bitboard), '\n');
  std::vector<std::string> actual_parts =
      absl::StrSplit(std::format("{}", actual_bitboard), '\n');

  *result_listener << "\n\n"
                   << "      Expected:                Actual:\n"
                   << "      ---------                -------";

  for (int i = 0; i < expected_parts.size(); ++i) {
    *result_listener << '\n'
                     << expected_parts[i] << "      " << actual_parts[i];
    if (expected_parts[i] != actual_parts[i]) {
      *result_listener << "  <-";
    }
  }

  return false;
}

MATCHER_P(EqualsPosition, expected, "") {
  std::expected<Position, std::string> result = TryMakePosition(expected);
  if (!result.has_value()) {
    *result_listener << "could not parse position: " << result.error();
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

  *result_listener << "\n\n"
                   << "      Expected:                Actual:\n"
                   << "      ---------                -------";

  for (int i = 0; i < expected_parts.size(); ++i) {
    *result_listener << '\n'
                     << expected_parts[i] << "      " << actual_parts[i];
    if (expected_parts[i] != actual_parts[i]) {
      *result_listener << "  <-";
    }
  }

  return false;
}

}  // namespace chessengine

#endif  // CHESS_ENGINE_TESTING_H_
