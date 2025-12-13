#include "command.h"

#include <format>
#include <string>
#include <string_view>
#include <vector>

namespace follychess {
namespace {

template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};

}  // namespace

CommandDispatcher &CommandDispatcher::Add(std::string arg,
                                          std::unique_ptr<Command> command) {
  command_map_[std::move(arg)] = std::move(command);
  return *this;
}

CommandDispatcher &CommandDispatcher::Add(std::string arg,
                                          CommandDispatcher dispatcher) {
  command_map_[std::move(arg)] = std::move(dispatcher);
  return *this;
}

[[nodiscard]] std::expected<void, std::string> CommandDispatcher::Run(
    std::vector<std::string_view> args) {
  if (args.empty() || args[0].empty()) {
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
                    },
                    it->second);
}

}  // namespace follychess
