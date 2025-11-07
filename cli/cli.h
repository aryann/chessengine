#ifndef CHESS_ENGINE_CLI_CLI_H_
#define CHESS_ENGINE_CLI_CLI_H_

#include "command.h"
#include "engine/position.h"

namespace chessengine {

struct CommandState {
  Position position;
};

CommandDispatcher MakeCommandDispatcher(CommandState& state);

}  // namespace chessengine

#endif  // CHESS_ENGINE_CLI_CLI_H_
