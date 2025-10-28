#ifndef CHESS_ENGINE_CLI_COMMAND_H_
#define CHESS_ENGINE_CLI_COMMAND_H_

#include <string>
#include <string_view>
#include <vector>

#include "perft.h"
#include "position.h"

namespace chessengine {

class Command {
public:
    virtual ~Command() = default;

    [[nodiscard]] virtual std::expected<void, std::string> Run(std::vector<std::string_view> args) = 0;
};

template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

class CommandDispatcher {
public:
    CommandDispatcher() = default;

    CommandDispatcher &Add(std::string arg, std::unique_ptr<Command> command) {
        command_map_[std::move(arg)] = std::move(command);
        return *this;
    }

    CommandDispatcher &Add(std::string arg, CommandDispatcher dispatcher) {
        command_map_[std::move(arg)] = std::move(dispatcher);
        return *this;
    }

    [[nodiscard]] std::expected<void, std::string> Run(std::vector<std::string_view> args) {
        if (args.empty() || args[0] == "") {
            return {};
        }

        auto it = command_map_.find(args[0]);
        if (it == command_map_.end()) {
            return std::unexpected(std::format("Invalid command: {}", args));
        }

        std::vector<std::string_view> remaining_args(args.begin() + 1, args.end());

        return std::visit(overloaded{
                                  [&](std::unique_ptr<Command> &command) {
                                      return command->Run(remaining_args);
                                  },
                                  [&](CommandDispatcher &dispatcher) {
                                      return dispatcher.Run(remaining_args);
                                  },
                          }, it->second);
    }

private:
    std::map<std::string, std::variant<std::unique_ptr<Command>, CommandDispatcher>, std::less<> > command_map_;
};

} // namespace chessengine

#endif // CHESS_ENGINE_CLI_COMMAND_H_
