#ifndef CHESS_ENGINE_CLI_CLI_H_
#define CHESS_ENGINE_CLI_CLI_H_

#include "command.h"
#include "engine/game.h"
#include "engine/position.h"

namespace chessengine {

struct CommandState {
  Game game;
};

CommandDispatcher MakeCommandDispatcher(CommandState& state);

}  // namespace chessengine

#endif  // CHESS_ENGINE_CLI_CLI_H_
