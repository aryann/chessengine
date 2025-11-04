#include <iostream>
#include <string_view>

#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "command.h"
#include "commands/display.h"
#include "commands/perft_command.h"
#include "commands/position_command.h"
#include "engine/move_generator.h"
#include "engine/position.h"

[[noreturn]] int main(int argc, char **argv) {
  std::println("Welcome!");
  std::println();

  using ::chessengine::Command;
  using ::chessengine::CommandDispatcher;
  using ::chessengine::Display;
  using ::chessengine::FenPos;
  using ::chessengine::PerftCommand;
  using ::chessengine::Position;
  using ::chessengine::StartPos;

  Position position = Position::Starting();

  CommandDispatcher dispatcher;

  CommandDispatcher position_commands;
  position_commands.Add("fen", std::make_unique<FenPos>(position));
  position_commands.Add("startpos", std::make_unique<StartPos>(position));

  dispatcher.Add("position", std::move(position_commands));

  CommandDispatcher go_commands;
  go_commands.Add("perft", std::make_unique<PerftCommand>(position));

  dispatcher.Add("go", std::move(go_commands));

  dispatcher.Add("d", std::make_unique<Display>(position));

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
