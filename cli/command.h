#ifndef CHESS_ENGINE_CLI_COMMAND_H_
#define CHESS_ENGINE_CLI_COMMAND_H_

#include <expected>
#include <map>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace chessengine {

class Command {
public:
    virtual ~Command() = default;

    [[nodiscard]] virtual std::expected<void, std::string> Run(std::vector<std::string_view> args) = 0;
};

class CommandDispatcher {
public:
    CommandDispatcher() = default;

    CommandDispatcher &Add(std::string arg, std::unique_ptr<Command> command);

    CommandDispatcher &Add(std::string arg, CommandDispatcher dispatcher);

    [[nodiscard]] std::expected<void, std::string> Run(std::vector<std::string_view> args);

private:
    std::map<std::string, std::variant<std::unique_ptr<Command>, CommandDispatcher>, std::less<> > command_map_;
};

} // namespace chessengine

#endif // CHESS_ENGINE_CLI_COMMAND_H_
