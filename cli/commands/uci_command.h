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
  explicit Go(const SearchFunc& search_func, Position& position)
      : search_func_(search_func), position_(position) {}

  std::expected<void, std::string> Run(
      std::vector<std::string_view> args) override {
    constexpr static int kDepth = 6;
    Move move = search_func_(position_, kDepth);
    std::println(std::cout, "bestmove {}", move);
    return {};
  }

 private:
  SearchFunc search_func_;
  Position& position_;
};

}  // namespace chessengine

#endif  // CHESS_ENGINE_CLI_COMMANDS_UCI_COMMAND_H_
