#include "testing.h"

#include <format>
#include <ostream>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "bitboard.h"

namespace chessengine {

using namespace ::std::literals;

void PrintTo(const Bitboard &bitboard, std::ostream *os) {
    *os << std::format("Bitboard(0x{:})", bitboard.Data());
}

std::string TestPositionToFen(std::string_view input) {
    std::vector<std::string_view> parts = absl::StrSplit(input, "a b c d e f g h");
    CHECK(parts.size() == 2) << "Invalid position input: " << input;

    std::string fen_board;

    std::string_view board = parts[0];
    int square = 0;
    int empty_count = 0;
    for (char curr: board) {
        if ("PNBRQKpnbrqk."s.find(curr) == std::string::npos) {
            continue;
        }

        if (curr == '.') {
            empty_count++;
        } else {
            if (empty_count > 0) {
                fen_board += std::to_string(empty_count);
                empty_count = 0;
            }
            fen_board += curr;
        }

        if ((square + 1) % 8 == 0) {
            if (empty_count > 0) {
                fen_board += std::to_string(empty_count);
                empty_count = 0;
            }
            if (square != kNumSquares - 1) {
                fen_board += '/';
            }
        }

        ++square;
    }

    return absl::StrCat(fen_board, " ", absl::StripAsciiWhitespace(parts[1]));
}

Position MakePosition(std::string_view input, std::source_location location) {
    std::expected<Position, std::string> position = Position::FromFen(
            TestPositionToFen(input));

    if (!position.has_value()) {
        LOG(FATAL)
            << location.file_name() << ":" << location.line() << ": "
            << "Invalid position: " << position.error();
    }

    return position.value();
}

} // namespace chessengine
