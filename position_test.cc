#include "position.h"

#include <expected>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::IsFalse;
using ::testing::IsTrue;

TEST(FEN, Initial) {
    std::expected<Position, std::string> position = Position::FromFen(
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

TEST(FEN, Kiwipete) {
    std::expected<Position, std::string> position = Position::FromFen(
            "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");

    ASSERT_THAT(position.has_value(), IsTrue()) << position.error();
    EXPECT_THAT(std::format("{}", position.value()), Eq(
                    "8: r . . . k . . r\n"
                    "7: p . p p q p b .\n"
                    "6: b n . . p n p .\n"
                    "5: . . . P N . . .\n"
                    "4: . p . . P . . .\n"
                    "3: . . N . . Q . p\n"
                    "2: P P P B B P P P\n"
                    "1: R . . . K . . R\n"
                    "   a b c d e f g h\n"
                    "\n"
                    "      Turn: -\n"
                    "  Castling: -\n"
                    "En Passant: -\n"
                    "Half Moves: 0\n"
                    "Full Moves: 0\n"
                ));
}

TEST(FEN, Sparse) {
    std::expected<Position, std::string> position = Position::FromFen(
            "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");

    ASSERT_THAT(position.has_value(), IsTrue()) << position.error();
    EXPECT_THAT(std::format("{}", position.value()), Eq(
                    "8: . . . . . . . .\n"
                    "7: . . p . . . . .\n"
                    "6: . . . p . . . .\n"
                    "5: K P . . . . . r\n"
                    "4: . R . . . p . k\n"
                    "3: . . . . . . . .\n"
                    "2: . . . . P . P .\n"
                    "1: . . . . . . . .\n"
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
