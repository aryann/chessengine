#include <iostream>
#include <string_view>

#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "cli.h"

[[noreturn]] int main(int argc, char **argv) {
  std::println("Welcome!");
  std::println();

  using ::follychess::Command;
  using ::follychess::CommandDispatcher;
  using ::follychess::CommandState;

  CommandState state;
  CommandDispatcher dispatcher = follychess::MakeCommandDispatcher(state);

  std::string command;
  while (true) {
    std::getline(std::cin, command);
    std::vector<std::string_view> parts = absl::StrSplit(
        command, absl::ByAsciiWhitespace(), absl::SkipWhitespace());

    auto error = dispatcher.Run(parts);
    if (!error.has_value()) {
      std::println(stderr, "{}", error.error());
    }
  }
}
