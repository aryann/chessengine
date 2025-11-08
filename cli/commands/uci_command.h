#ifndef CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_
#define CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_

#include <iostream>
#include <print>

#include "cli/command.h"

namespace chessengine {

class Uci : public Command {
 public:
  Uci() = default;

  ~Uci() override = default;

  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override {
    std::println(std::cout, "id name chessengine");
    std::println(std::cout, "id author Aryan Naraghi");
    std::println(std::cout, "uciok");
    return {};
  }
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_
