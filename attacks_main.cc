#include <format>
#include <iostream>

#include "attacks.h"
#include "types.h"

int main(int argc, char **argv) {
    std::println("{}", chessengine::kPseudoAttacks[chessengine::kKnight][chessengine::H2]);

    chessengine::Bitboard board = chessengine::kEmptyBoard;

    board.Set(chessengine::D4);
    std::println("{}", board);
    std::println("{}", board.Shift<chessengine::kSouthWest>());
    return 0;
}
