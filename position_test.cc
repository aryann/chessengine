#include "position.h"

#include <expected>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "testing.h"

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::IsFalse;
using ::testing::IsTrue;

TEST(Position, Starting) {
    EXPECT_THAT(Position::Starting(), EqualsPosition(
                    "8: r n b q k b n r"
                    "7: p p p p p p p p"
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: P P P P P P P P"
                    "1: R N B Q K B N R"
                    "   a b c d e f g h"
                    //
                    "   w KQkq - 0 1"));
}

TEST(FEN, Starting) {
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
                    "   w KQkq - 0 1\n"
                ));
}

TEST(FEN, CastlingRights) {
    //
    {
        std::expected<Position, std::string> position = Position::FromFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1");

        ASSERT_THAT(position.has_value(), IsTrue()) << position.error();
        auto castling_rights = position.value().GetCastlingRights();
        EXPECT_THAT(std::format("{}", castling_rights), Eq("-"));
    }
    //
    {
        std::expected<Position, std::string> position = Position::FromFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        ASSERT_THAT(position.has_value(), IsTrue()) << position.error();
        auto castling_rights = position.value().GetCastlingRights();
        EXPECT_THAT(std::format("{}", castling_rights), Eq("KQkq"));
    }
    //
    {
        std::expected<Position, std::string> position = Position::FromFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w kq - 0 1");

        ASSERT_THAT(position.has_value(), IsTrue()) << position.error();
        auto castling_rights = position.value().GetCastlingRights();
        EXPECT_THAT(std::format("{}", castling_rights), Eq("kq"));
    }
    //
    {
        std::expected<Position, std::string> position = Position::FromFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Kk - 0 1");

        ASSERT_THAT(position.has_value(), IsTrue()) << position.error();
        auto castling_rights = position.value().GetCastlingRights();
        EXPECT_THAT(std::format("{}", castling_rights), Eq("Kk"));
    }
    //
    {
        std::expected<Position, std::string> position = Position::FromFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w INVALID - 0 1");

        ASSERT_THAT(position.has_value(), IsFalse());
        EXPECT_THAT(position.error(), Eq("Invalid castling rights: INVALID"));
    }
}

TEST(FEN, HalfMoves) {
    //
    {
        std::expected<Position, std::string> position = Position::FromFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 30 1");

        ASSERT_THAT(position.has_value(), IsTrue()) << position.error();
        EXPECT_THAT(position.value().GetHalfMoves(), Eq(30));
    }
    //
    {
        std::expected<Position, std::string> position = Position::FromFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - INVALID 1");

        ASSERT_THAT(position.has_value(), IsFalse());
        EXPECT_THAT(position.error(), Eq("Invalid half moves: INVALID"));
    }
}

TEST(FEN, FullMoves) {
    //
    {
        std::expected<Position, std::string> position = Position::FromFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 50");

        ASSERT_THAT(position.has_value(), IsTrue()) << position.error();
        EXPECT_THAT(position.value().GetFullMoves(), Eq(50));
    }
    //
    {
        std::expected<Position, std::string> position = Position::FromFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 INVALID");

        ASSERT_THAT(position.has_value(), IsFalse());
        EXPECT_THAT(position.error(), Eq("Invalid full moves: INVALID"));
    }
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
                    "   w KQkq - 0 1\n"
                ));
}

TEST(FEN, Sparse) {
    std::expected<Position, std::string> position = Position::FromFen(
            "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - a3 0 1");

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
                    "   w - a3 0 1\n"
                ));
}

TEST(Position, DoMove) {
    Position position = Position::Starting();

    position.DoMove(Move(B1, C3));
    EXPECT_THAT(position, EqualsPosition(
                    "8: r n b q k b n r"
                    "7: p p p p p p p p"
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . N . . . . ."
                    "2: P P P P P P P P"
                    "1: R . B Q K B N R"
                    "   a b c d e f g h"
                    //
                    "   b KQkq - 1 1"));

    position.DoMove(Move(D7, D5));
    EXPECT_THAT(position, EqualsPosition(
                    "8: r n b q k b n r"
                    "7: p p p . p p p p"
                    "6: . . . . . . . ."
                    "5: . . . p . . . ."
                    "4: . . . . . . . ."
                    "3: . . N . . . . ."
                    "2: P P P P P P P P"
                    "1: R . B Q K B N R"
                    "   a b c d e f g h"
                    //
                    "   w KQkq - 2 2"));

    position.DoMove(Move(C3, D5));
    EXPECT_THAT(position, EqualsPosition(
                    "8: r n b q k b n r"
                    "7: p p p . p p p p"
                    "6: . . . . . . . ."
                    "5: . . . N . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: P P P P P P P P"
                    "1: R . B Q K B N R"
                    "   a b c d e f g h"
                    //
                    "   b KQkq - 3 2"));

}

} // namespace
} // namespace chessengine
