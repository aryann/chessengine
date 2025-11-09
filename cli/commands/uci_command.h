#ifndef CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_
#define CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_

#include <iostream>
#include <print>

#include "cli/command.h"

namespace chessengine {

class Uci : public Command {
 public:
  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override {
    std::println(std::cout, "id name chessengine");
    std::println(std::cout, "id author Aryan Naraghi");
    std::println(std::cout, "uciok");
    return {};
  }
};

class Quit : public Command {
  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override {
    std::exit(0);
  }
};

class Go : public Command {
 public:
  explicit Go(Position& position) : position_(position) {}

  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override {
    if (position_.SideToMove() == kWhite) {
      std::println(std::cout, "bestmove e2e4");
    } else {
      std::println(std::cout, "bestmove e7e5");
    }
    return {};
  }

 private:
  Position& position_;
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_
