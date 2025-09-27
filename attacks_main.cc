#include <format>
#include <iostream>

#include "attacks.h"

int main(int argc, char **argv) {
    std::ostream_iterator<char> out(std::cout);

    std::format_to(out, "{}\n", chessengine::kPseudoAttacks[0][0]);
    return 0;
}
