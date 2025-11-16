#ifndef CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_
#define CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_

#include <iostream>
#include <print>

#include "cli/command.h"
#include "search/search.h"

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
    constexpr static int kDefaultSearchDepth = 6;
    int depth = kDefaultSearchDepth;

    if (!args.empty()) {
      if (args.front() == "depth") {
        if (args.size() != 2) {
          return std::unexpected(std::format("Invalid go command: {}", args));
        }

        depth = std::stoi(std::string(args.back()));
      }
    }

    Move move = Search(position_,
                       SearchOptions().SetDepth(depth).SetLogEveryN(1 << 10));
    std::println(std::cout, "bestmove {}", move);
    return {};
  }

 private:
  Position& position_;
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_
