#include <format>
#include <iostream>

#include "attacks.h"
#include "types.h"

int main(int argc, char **argv) {
    std::ostream_iterator<char> out(std::cout);

    //std::format_to(out, "{}\n", chessengine::kPseudoAttacks[chessengine::kBlackPawn][chessengine::H2]);

    chessengine::Bitboard board = chessengine::kEmptyBoard;

    board = Set(board, chessengine::D4);
    std::format_to(out, "{}\n", board);
    std::format_to(out, "{}\n", chessengine::Shift<chessengine::kSouthWest>(board));
    return 0;
}
