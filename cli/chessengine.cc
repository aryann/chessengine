#include <iostream>
#include <string_view>

#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "command.h"
#include "move_generator.h"
#include "perft.h"
#include "position.h"

namespace chessengine {

std::optional<Move> FindMove(std::string_view uci_move, const std::vector<Move> &moves) {
    for (const Move &move: moves) {
        if (std::format("{}", move) == uci_move) {
            return move;
        }
    }
    return std::nullopt;
}

void ApplyMoves(const std::vector<std::string_view> &uci_moves, Position &position) {
    for (std::string_view uci_move: uci_moves) {
        std::vector<Move> moves;
        if (position.GetCheckers(position.SideToMove())) {
            moves = GenerateMoves<kEvasion>(position);
        } else {
            moves = GenerateMoves<kQuiet, kCapture>(position);
        }

        std::optional<Move> move = FindMove(uci_move, moves);
        if (!move) {
            std::println(stderr, "Invalid move: {}", uci_move);
            return;
        }

        position.Do(*move);
        if (position.GetCheckers(~position.SideToMove())) {
            std::println(stderr, "Move places side in check: {}", uci_move);
            return;
        }
    }
}

} // namespace chessengine

int main(int argc, char **argv) {
    std::println("Welcome!");
    std::println();

    using ::chessengine::CommandDispatcher;
    using ::chessengine::Command;
    using ::chessengine::Display;
    using ::chessengine::StartPos;
    using ::chessengine::FenPos;
    using ::chessengine::PerftCommand;
    using ::chessengine::Position;

    Position position = Position::Starting();

    CommandDispatcher dispatcher;

    CommandDispatcher position_commands;
    position_commands.Add("fen", std::make_unique<FenPos>(position));
    position_commands.Add("startpos", std::make_unique<StartPos>(position));

    dispatcher.Add(
            "position", std::move(position_commands));

    CommandDispatcher go_commands;
    go_commands.Add("perft", std::make_unique<PerftCommand>(position));

    dispatcher.Add("go", std::move(go_commands));

    dispatcher.Add("d", std::make_unique<Display>(position));

    std::string command;
    while (true) {
        std::getline(std::cin, command);
        std::vector<std::string_view> parts = absl::StrSplit(
                command, absl::ByAsciiWhitespace(), absl::SkipWhitespace());

        auto error = dispatcher.Run(parts);
        if (!error.has_value()) {
            std::println(stderr, "{}", error.error());
        }
    }

    return 0;
}

