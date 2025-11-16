#include "position_command.h"

#include <format>

#include "engine/move.h"
#include "engine/move_generator.h"

namespace chessengine {
namespace {

std::optional<Move> FindMove(std::string_view uci_move,
                             const std::vector<Move> &moves) {
  for (const Move &move : moves) {
    if (std::format("{}", move) == uci_move) {
      return move;
    }
  }
  return std::nullopt;
}

std::expected<void, std::string> ApplyMoves(
    const std::vector<std::string_view> &uci_moves, Position &position) {
  if (uci_moves.empty()) {
    return {};
  }
  if (uci_moves.front() != "moves") {
    return std::unexpected(
        std::format("Invalid remainder for position command: {}", uci_moves));
  }

  for (int i = 1; i < uci_moves.size(); ++i) {
    std::vector<Move> moves = GenerateMoves(position);

    std::optional<Move> move = FindMove(uci_moves[i], moves);
    if (!move) {
      return std::unexpected(std::format("Illegal move: {}", uci_moves[i]));
    }

    position.Do(*move);
    if (position.GetCheckers(~position.SideToMove())) {
      return std::unexpected(std::format(
          "Illegal move (cannot place own king in check): {}", *move));
    }
  }

  return {};
}

}  // namespace

std::expected<void, std::string> StartPos::Run(
    std::vector<std::string_view> args) {
  position_ = Position::Starting();
  return ApplyMoves(args, position_);
}

std::expected<void, std::string> FenPos::Run(
    std::vector<std::string_view> args) {
  auto result = Position::FromFen({
      args.begin(),
      args.begin() + std::min(static_cast<std::size_t>(6), args.size()),
  });
  if (!result.has_value()) {
    return std::unexpected(result.error());
  }

  position_ = result.value();
  return ApplyMoves({args.begin() + 6, args.end()}, position_);
}

}  // namespace chessengine
