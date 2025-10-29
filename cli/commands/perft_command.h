#ifndef CHESS_ENGINE_CLI_COMMANDS_PERFT_COMMAND_H_
#define CHESS_ENGINE_CLI_COMMANDS_PERFT_COMMAND_H_

#include <string>
#include <string_view>
#include <vector>

#include "cli/command.h"
#include "perft.h"
#include "position.h"

namespace chessengine {

class PerftCommand : public Command {
public:
    explicit PerftCommand(const Position &position):
        position_(position) {
    }

    ~PerftCommand() override = default;

    std::expected<void, std::string> Run(std::vector<std::string_view> args) override {
        int depth = 1;
        if (!args.empty()) {
            depth = std::stoi(std::string(args[0]));
        }

        std::vector<std::size_t> depth_counts;
        std::map<Move, std::size_t> final_move_counts;
        RunPerft(depth, position_, depth_counts, final_move_counts);

        for (auto [move, count]: final_move_counts) {
            std::println("{}: {}", move, count);
        }

        std::println();
        std::println("Nodes searched: {}", depth_counts.back());
        return {};
    }

private:
    Position position_;
};

} // namespace chessengine

#endif // CHESS_ENGINE_CLI_COMMANDS_PERFT_COMMAND_H_
