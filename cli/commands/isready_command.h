#ifndef CHESS_ENGINE_CLI_COMMANDS_ISREADY_COMMAND_H_
#define CHESS_ENGINE_CLI_COMMANDS_ISREADY_COMMAND_H_

#include <print>

#include "cli/command.h"

namespace chessengine {

class IsReady : public Command {
 public:
  IsReady() = default;

  ~IsReady() override = default;

  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override {
    std::println("readyok");
    return {};
  }
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_CLI_COMMANDS_ISREADY_COMMAND_H_
