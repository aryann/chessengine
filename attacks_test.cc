#include "attacks.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using testing::Eq;

TEST(Attacks, WhitePawns) {
    EXPECT_THAT(std::format("{}", kPseudoAttacks[kWhitePawn][A2]), Eq(
                    "8: . . . . . . . .\n"
                    "7: . . . . . . . .\n"
                    "6: . . . . . . . .\n"
                    "5: . . . . . . . .\n"
                    "4: . . . . . . . .\n"
                    "3: . X . . . . . .\n"
                    "2: . . . . . . . .\n"
                    "1: . . . . . . . .\n"
                    "   a b c d e f g h\n"
                ));
    EXPECT_THAT(std::format("{}", kPseudoAttacks[kWhitePawn][B2]), Eq(
                    "8: . . . . . . . .\n"
                    "7: . . . . . . . .\n"
                    "6: . . . . . . . .\n"
                    "5: . . . . . . . .\n"
                    "4: . . . . . . . .\n"
                    "3: X . X . . . . .\n"
                    "2: . . . . . . . .\n"
                    "1: . . . . . . . .\n"
                    "   a b c d e f g h\n"
                ));
    EXPECT_THAT(std::format("{}", kPseudoAttacks[kWhitePawn][H2]), Eq(
                    "8: . . . . . . . .\n"
                    "7: . . . . . . . .\n"
                    "6: . . . . . . . .\n"
                    "5: . . . . . . . .\n"
                    "4: . . . . . . . .\n"
                    "3: . . . . . . X .\n"
                    "2: . . . . . . . .\n"
                    "1: . . . . . . . .\n"
                    "   a b c d e f g h\n"
                ));

    EXPECT_THAT(std::format("{}", kPseudoAttacks[kWhitePawn][A1]), Eq(
                    "8: . . . . . . . .\n"
                    "7: . . . . . . . .\n"
                    "6: . . . . . . . .\n"
                    "5: . . . . . . . .\n"
                    "4: . . . . . . . .\n"
                    "3: . . . . . . . .\n"
                    "2: . . . . . . . .\n"
                    "1: . . . . . . . .\n"
                    "   a b c d e f g h\n"
                ));
    EXPECT_THAT(std::format("{}", kPseudoAttacks[kWhitePawn][E1]), Eq(
                    "8: . . . . . . . .\n"
                    "7: . . . . . . . .\n"
                    "6: . . . . . . . .\n"
                    "5: . . . . . . . .\n"
                    "4: . . . . . . . .\n"
                    "3: . . . . . . . .\n"
                    "2: . . . . . . . .\n"
                    "1: . . . . . . . .\n"
                    "   a b c d e f g h\n"
                ));

    EXPECT_THAT(std::format("{}", kPseudoAttacks[kWhitePawn][A8]), Eq(
                    "8: . . . . . . . .\n"
                    "7: . . . . . . . .\n"
                    "6: . . . . . . . .\n"
                    "5: . . . . . . . .\n"
                    "4: . . . . . . . .\n"
                    "3: . . . . . . . .\n"
                    "2: . . . . . . . .\n"
                    "1: . . . . . . . .\n"
                    "   a b c d e f g h\n"
                ));
    EXPECT_THAT(std::format("{}", kPseudoAttacks[kWhitePawn][H8]), Eq(
                    "8: . . . . . . . .\n"
                    "7: . . . . . . . .\n"
                    "6: . . . . . . . .\n"
                    "5: . . . . . . . .\n"
                    "4: . . . . . . . .\n"
                    "3: . . . . . . . .\n"
                    "2: . . . . . . . .\n"
                    "1: . . . . . . . .\n"
                    "   a b c d e f g h\n"
                ));
}

} // namespace
} // namespace chessengine

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
