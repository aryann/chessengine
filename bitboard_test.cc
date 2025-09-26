#include "bitboard.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using testing::Eq;

TEST(Formatter, Ranks) {
    EXPECT_THAT(std::format("{}", rank::k1),
                Eq(
                    "8: . . . . . . . .\n"
                    "7: . . . . . . . .\n"
                    "6: . . . . . . . .\n"
                    "5: . . . . . . . .\n"
                    "4: . . . . . . . .\n"
                    "3: . . . . . . . .\n"
                    "2: . . . . . . . .\n"
                    "1: 1 1 1 1 1 1 1 1\n"
                    "   a b c d e f g h\n"
                ));
    EXPECT_THAT(std::format("{}", rank::k5),
                Eq(
                    "8: . . . . . . . .\n"
                    "7: . . . . . . . .\n"
                    "6: . . . . . . . .\n"
                    "5: 1 1 1 1 1 1 1 1\n"
                    "4: . . . . . . . .\n"
                    "3: . . . . . . . .\n"
                    "2: . . . . . . . .\n"
                    "1: . . . . . . . .\n"
                    "   a b c d e f g h\n"
                ));
    EXPECT_THAT(std::format("{}", rank::k8),
                Eq(
                    "8: 1 1 1 1 1 1 1 1\n"
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

TEST(Formatter, Files) {
    EXPECT_THAT(std::format("{}", file::kA),
                Eq(
                    "8: 1 . . . . . . .\n"
                    "7: 1 . . . . . . .\n"
                    "6: 1 . . . . . . .\n"
                    "5: 1 . . . . . . .\n"
                    "4: 1 . . . . . . .\n"
                    "3: 1 . . . . . . .\n"
                    "2: 1 . . . . . . .\n"
                    "1: 1 . . . . . . .\n"
                    "   a b c d e f g h\n"
                ));
    EXPECT_THAT(std::format("{}", file::kD),
                Eq(
                    "8: . . . 1 . . . .\n"
                    "7: . . . 1 . . . .\n"
                    "6: . . . 1 . . . .\n"
                    "5: . . . 1 . . . .\n"
                    "4: . . . 1 . . . .\n"
                    "3: . . . 1 . . . .\n"
                    "2: . . . 1 . . . .\n"
                    "1: . . . 1 . . . .\n"
                    "   a b c d e f g h\n"
                ));
    EXPECT_THAT(std::format("{}", file::kH),
                Eq(
                    "8: . . . . . . . 1\n"
                    "7: . . . . . . . 1\n"
                    "6: . . . . . . . 1\n"
                    "5: . . . . . . . 1\n"
                    "4: . . . . . . . 1\n"
                    "3: . . . . . . . 1\n"
                    "2: . . . . . . . 1\n"
                    "1: . . . . . . . 1\n"
                    "   a b c d e f g h\n"
                ));
}

TEST(Formatter, Corners) {
    Bitboard back_ranks = rank::k1 | rank::k8;

    Bitboard board = 0;
    board |= file::kA & back_ranks;
    board |= file::kH & back_ranks;

    EXPECT_THAT(std::format("{}", board),
                Eq(
                    "8: 1 . . . . . . 1\n"
                    "7: . . . . . . . .\n"
                    "6: . . . . . . . .\n"
                    "5: . . . . . . . .\n"
                    "4: . . . . . . . .\n"
                    "3: . . . . . . . .\n"
                    "2: . . . . . . . .\n"
                    "1: 1 . . . . . . 1\n"
                    "   a b c d e f g h\n"
                ));
}

} // namespace
} // namespace chessengine

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
