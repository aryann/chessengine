#ifndef CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_
#define CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_

#include <print>

#include "cli/command.h"

namespace chessengine {

class Uci : public Command {
 public:
  Uci() = default;

  ~Uci() override = default;

  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override {
    std::println("id name chessengine");
    std::println("id author Aryan Naraghi");
    std::println("uciok");
    return {};
  }
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_
