#include <iostream>
#include <string_view>

#include "absl/strings/str_split.h"
#include "perft.h"
#include "position.h"

namespace chessengine {

void SetPositionCommand(std::string_view input, Position &position) {
    if (input == "startpos") {
        position = Position::Starting();
        return;
    }

    auto result = Position::FromFen(input);
    if (!result.has_value()) {
        std::println(stderr, "Invalid position: {}", result.error());
        return;
    }
    position = result.value();
}

void RunPerftCommand(std::string_view args, Position &position) {
    int depth = std::stoi(std::string(args));

    std::vector<std::size_t> depth_counts;
    std::map<Move, std::size_t> final_move_counts;
    RunPerft(depth, position, depth_counts, final_move_counts);

    for (auto [move, count]: final_move_counts) {
        std::cout << move << ": " << count << '\n';
    }

    std::println();
    std::println("Nodes searched: {}", depth_counts.back());
}

void RunLoop() {
    chessengine::Position position = chessengine::Position::Starting();

    std::string command;
    while (true) {
        std::getline(std::cin, command);
        if (command.empty()) {
            continue;
        }

        std::vector<std::string_view> parts = absl::StrSplit(
                command, absl::MaxSplits(absl::ByAsciiWhitespace(), 1));
        if (parts.size() != 2) {
            std::println(stderr, "Invalid command: {}", command);
            continue;
        }

        std::string_view args = parts[1];

        if (parts[0] == "position") {
            SetPositionCommand(args, position);
        } else if (parts[0] == "perft") {
            RunPerftCommand(args, position);
        } else {
            std::println(stderr, "Invalid command: {}", command);
        }

        std::println();
    }
}

} // namespace chessengine

int main(int argc, char **argv) {
    std::println("Welcome!");
    std::println();

    chessengine::RunLoop();
    return 0;
}

