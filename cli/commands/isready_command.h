#ifndef CHESS_ENGINE_CLI_COMMANDS_ISREADY_COMMAND_H_
#define CHESS_ENGINE_CLI_COMMANDS_ISREADY_COMMAND_H_

#include <iostream>
#include <print>

#include "cli/command.h"

namespace follychess {

class IsReady : public Command {
 public:
  IsReady() = default;

  ~IsReady() override = default;

  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override {
    std::println(std::cout, "readyok");
    return {};
  }
};

}  // namespace follychess

#endif  // CHESS_ENGINE_CLI_COMMANDS_ISREADY_COMMAND_H_
