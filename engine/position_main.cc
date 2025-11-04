#include <format>
#include <iostream>

#include "position.h"

int main(int argc, char **argv) {
  std::string_view fen =
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  if (argc == 2) {
    fen = argv[1];
  }

  auto result = chessengine::Position::FromFen(fen);
  if (!result.has_value()) {
    std::println("{}", result.error());
    return 1;
  }

  std::println("{}", result.value());
  return 0;
}
