#include <iostream>
#include <string_view>

#include "move_generator.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
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

void SetPositionCommand(std::vector<std::string_view> parts, Position &position) {
    if (parts.empty()) {
        std::println(stderr, "Invalid position command: {}", parts);
        return;
    }

    if (parts[0] == "startpos") {
        position = Position::Starting();
        parts = {parts.begin() + 1, parts.end()};

    } else if (parts[0] == "moves") {
        position = Position::Starting();

    } else if (parts[0] == "fen") {
        if (parts.size() < 7) {
            std::println(stderr, "Invalid position command: {}", parts);
            return;
        }

        std::string fen = absl::StrJoin(parts.begin() + 1, parts.begin() + 7, " ");
        auto result = Position::FromFen(fen);
        if (!result.has_value()) {
            std::println(stderr, "Invalid position: {}", result.error());
            return;
        }
        position = result.value();
        parts = {parts.begin() + 7, parts.end()};
    }

    if (parts.empty()) {
        return;
    }

    if (parts[0] != "moves") {
        std::println(stderr, "Invalid position command: {}", parts);
        return;
    }

    std::vector<std::string_view> uci_moves = {parts.begin() + 1, parts.end()};
    ApplyMoves(uci_moves, position);
}

void RunPerftCommand(std::vector<std::string_view> parts, Position &position) {
    int depth = 1;
    if (!parts.empty()) {
        depth = std::stoi(std::string(parts[0]));
    }

    std::vector<std::size_t> depth_counts;
    std::map<Move, std::size_t> final_move_counts;
    RunPerft(depth, position, depth_counts, final_move_counts);

    for (auto [move, count]: final_move_counts) {
        std::println("{}: {}", move, count);
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
                command, absl::ByAsciiWhitespace());


        if (parts[0] == "position") {
            SetPositionCommand({parts.begin() + 1, parts.end()}, position);
        } else if (parts[0] == "perft") {
            RunPerftCommand({parts.begin() + 1, parts.end()}, position);
        } else if (parts[0] == "d") {
            std::println("{}", position);
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

