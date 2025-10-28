#ifndef CHESS_ENGINE_CLI_COMMANDS_POSITION_COMMAND_H_
#define CHESS_ENGINE_CLI_COMMANDS_POSITION_COMMAND_H_

#include <string>
#include <string_view>
#include <vector>

#include "position.h"
#include "cli/command.h"

namespace chessengine {

class StartPos : public Command {
public:
    explicit StartPos(Position &position):
        position_(position) {
    }

    ~StartPos() override = default;

    std::expected<void, std::string> Run(std::vector<std::string_view> args) override {
        position_ = Position::Starting();
        return {};
    }

private:
    Position &position_;
};

class FenPos : public Command {
public:
    explicit FenPos(Position &position):
        position_(position) {
    }

    ~FenPos() override = default;

    std::expected<void, std::string> Run(std::vector<std::string_view> args) override {
        auto result = Position::FromFen(args);
        if (result.has_value()) {
            position_ = result.value();
            return {};
        }

        return std::unexpected(result.error());
    }

private:
    Position &position_;
};

} // namespace chessengine

#endif // CHESS_ENGINE_CLI_COMMANDS_POSITION_COMMAND_H_
