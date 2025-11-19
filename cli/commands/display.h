#ifndef CHESS_ENGINE_CLI_COMMANDS_DISPLAY_H_
#define CHESS_ENGINE_CLI_COMMANDS_DISPLAY_H_

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "cli/command.h"
#include "engine/game.h"

namespace chessengine {
class Position;

class Display : public Command {
 public:
  explicit Display(const Game &game) : game_(game) {}

  ~Display() override = default;

  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override {
    std::println(std::cout, "{}", game_.GetPosition());
    return {};
  }

 private:
  const Game &game_;
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_CLI_COMMANDS_DISPLAY_H_
