#ifndef CHESS_ENGINE_CLI_COMMANDS_POSITION_COMMAND_H_
#define CHESS_ENGINE_CLI_COMMANDS_POSITION_COMMAND_H_

#include <string>
#include <string_view>
#include <vector>

#include "cli/command.h"
#include "engine/game.h"
#include "engine/position.h"

namespace follychess {

class StartPos : public Command {
 public:
  explicit StartPos(Game& game) : game_(game) {}

  ~StartPos() override = default;

  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override;

 private:
  Game& game_;
};

class FenPos : public Command {
 public:
  explicit FenPos(Game& game) : game_(game) {}

  ~FenPos() override = default;

  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override;

 private:
  Game& game_;
};

}  // namespace follychess

#endif  // CHESS_ENGINE_CLI_COMMANDS_POSITION_COMMAND_H_
