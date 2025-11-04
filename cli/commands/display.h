#ifndef CHESS_ENGINE_CLI_COMMANDS_DISPLAY_H_
#define CHESS_ENGINE_CLI_COMMANDS_DISPLAY_H_

#include <string>
#include <string_view>
#include <vector>

#include "cli/command.h"
#include "engine/position.h"

namespace chessengine {
class Position;

class Display : public Command {
 public:
  explicit Display(const Position &position) : position_(position) {}

  ~Display() override = default;

  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override {
    std::println("{}", position_);
    return {};
  }

 private:
  const Position &position_;
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_CLI_COMMANDS_DISPLAY_H_
