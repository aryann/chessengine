#ifndef FOLLYCHESS_CLI_CLI_H_
#define FOLLYCHESS_CLI_CLI_H_

#include "command.h"
#include "engine/game.h"
#include "engine/position.h"

namespace follychess {

struct CommandState {
  Game game;
};

CommandDispatcher MakeCommandDispatcher(CommandState& state);

}  // namespace follychess

#endif  // FOLLYCHESS_CLI_CLI_H_
