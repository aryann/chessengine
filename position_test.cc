#include "position.h"

#include <expected>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::IsFalse;
using ::testing::IsTrue;

TEST(FEN, Default) {
    std::expected<Position, std::string> position = Position::Make(
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    ASSERT_THAT(position.has_value(), IsTrue()) << position.error();
    EXPECT_THAT(std::format("{}", position.value()), Eq(
                    "8: r n b q k b n r\n"
                    "7: p p p p p p p p\n"
                    "6: . . . . . . . .\n"
                    "5: . . . . . . . .\n"
                    "4: . . . . . . . .\n"
                    "3: . . . . . . . .\n"
                    "2: P P P P P P P P\n"
                    "1: R N B Q K B N R\n"
                    "   a b c d e f g h\n"
                    "\n"
                    "      Turn: -\n"
                    "  Castling: -\n"
                    "En Passant: -\n"
                    "Half Moves: 0\n"
                    "Full Moves: 0\n"
                ));
}

} // namespace
} // namespace chessengine
