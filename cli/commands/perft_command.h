#ifndef FOLLYCHESS_CLI_COMMANDS_PERFT_COMMAND_H_
#define FOLLYCHESS_CLI_COMMANDS_PERFT_COMMAND_H_

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "cli/command.h"
#include "engine/game.h"
#include "engine/perft.h"

namespace follychess {

class PerftCommand : public Command {
 public:
  explicit PerftCommand(Game &game) : game_(game) {}

  ~PerftCommand() override = default;

  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override {
    int depth = 1;
    if (!args.empty()) {
      depth = std::stoi(std::string(args[0]));
    }

    std::vector<std::size_t> depth_counts;
    std::map<Move, std::size_t> final_move_counts;
    RunPerft(depth, game_.GetPosition(), depth_counts, final_move_counts);

    for (auto [move, count] : final_move_counts) {
      std::println(std::cout, "{}: {}", move, count);
    }

    std::println(std::cout);
    std::println(std::cout, "Nodes searched: {}", depth_counts.back());
    return {};
  }

 private:
  Game &game_;
};

}  // namespace follychess

#endif  // FOLLYCHESS_CLI_COMMANDS_PERFT_COMMAND_H_
