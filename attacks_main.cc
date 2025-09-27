#include <format>
#include <iostream>

#include "attacks.h"
#include "types.h"

int main(int argc, char **argv) {
    std::ostream_iterator<char> out(std::cout);

    std::format_to(out, "{}\n", chessengine::kPseudoAttacks[chessengine::kWhitePawn][chessengine::H2]);
    return 0;
}
