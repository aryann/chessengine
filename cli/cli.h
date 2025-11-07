#ifndef CHESS_ENGINE_CLI_CLI_H_
#define CHESS_ENGINE_CLI_CLI_H_

#include "command.h"
#include "engine/position.h"

namespace chessengine {

CommandDispatcher MakeCommandDispatcher(Position& position);

}  // namespace chessengine

#endif  // CHESS_ENGINE_CLI_CLI_H_
