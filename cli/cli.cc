#include "cli.h"

#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "command.h"
#include "commands/display.h"
#include "commands/perft_command.h"
#include "commands/position_command.h"
#include "engine/move_generator.h"
#include "engine/position.h"

namespace chessengine {

CommandDispatcher MakeCommandDispatcher(Position& position) {
  CommandDispatcher dispatcher;

  CommandDispatcher position_commands;
  position_commands.Add("fen", std::make_unique<FenPos>(position));
  position_commands.Add("startpos", std::make_unique<StartPos>(position));

  dispatcher.Add("position", std::move(position_commands));

  CommandDispatcher go_commands;
  go_commands.Add("perft", std::make_unique<PerftCommand>(position));

  dispatcher.Add("go", std::move(go_commands));

  dispatcher.Add("d", std::make_unique<Display>(position));

  return dispatcher;
}

}  // namespace chessengine