#include "cli.h"

#include "absl/strings/str_join.h"
#include "command.h"
#include "commands/display.h"
#include "commands/isready_command.h"
#include "commands/perft_command.h"
#include "commands/position_command.h"
#include "commands/uci_command.h"
#include "engine/move_generator.h"
#include "engine/position.h"
#include "search/random_search.h"

namespace chessengine {

CommandDispatcher MakeCommandDispatcher(CommandState& state) {
  Position& position = state.position;
  CommandDispatcher dispatcher;

  CommandDispatcher position_commands;
  position_commands.Add("fen", std::make_unique<FenPos>(position));
  position_commands.Add("startpos", std::make_unique<StartPos>(position));

  dispatcher.Add("position", std::move(position_commands));

  dispatcher.Add("perft", std::make_unique<PerftCommand>(position));

  dispatcher.Add("d", std::make_unique<Display>(position));
  dispatcher.Add("isready", std::make_unique<IsReady>());
  dispatcher.Add("uci", std::make_unique<Uci>());
  dispatcher.Add("go", std::make_unique<Go>(RandomSearch, position));
  dispatcher.Add("quit", std::make_unique<Quit>());

  return dispatcher;
}

}  // namespace chessengine