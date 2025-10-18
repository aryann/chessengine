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

constexpr std::string_view kStartingPosition =
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
        "   w KQkq - 0 1";

TEST(Position, Starting) {
    EXPECT_THAT(Position::Starting(), EqualsPosition(kStartingPosition));
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

TEST(Position, DoAndUndo) {
    Position position = Position::Starting();

    Move move_one(B1, C3);
    std::string_view position_one =
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
            "   b KQkq - 1 1";

    Move move_two(D7, D5);
    std::string_view position_two =
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
            "   w KQkq - 2 2";

    Move move_three(C3, D5, MoveOptions().SetCaptured(kPawn, 2));
    std::string_view position_three =
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
            "   b KQkq - 0 2";

    position.Do(move_one);
    EXPECT_THAT(position, EqualsPosition(position_one));

    position.Do(move_two);
    EXPECT_THAT(position, EqualsPosition(position_two));

    position.Do(move_three);
    EXPECT_THAT(position, EqualsPosition(position_three));

    position.Undo(move_three);
    EXPECT_THAT(position, EqualsPosition(position_two));

    position.Do(move_three);
    EXPECT_THAT(position, EqualsPosition(position_three));

    position.Undo(move_three);
    EXPECT_THAT(position, EqualsPosition(position_two));

    position.Undo(move_two);
    EXPECT_THAT(position, EqualsPosition(position_one));

    position.Undo(move_one);
    EXPECT_THAT(position, EqualsPosition(kStartingPosition));
}

TEST(GetPieces, StartingPosition) {
    Position position = Position::Starting();

    EXPECT_THAT(position.GetPieces(), EqualsBitboard(
                    "8: X X X X X X X X"
                    "7: X X X X X X X X"
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: X X X X X X X X"
                    "1: X X X X X X X X"
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(position.GetPieces(kWhite), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: X X X X X X X X"
                    "1: X X X X X X X X"
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kWhite, kPawn), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: X X X X X X X X"
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kWhite, kKnight), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . X . . . . X ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kWhite, kBishop), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . X . . X . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kWhite, kRook), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: X . . . . . . X"
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kWhite, kQueen), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . X . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kWhite, kKing), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . X . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(position.GetPieces(kBlack), EqualsBitboard(
                    "8: X X X X X X X X"
                    "7: X X X X X X X X"
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kBlack, kPawn), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: X X X X X X X X"
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kBlack, kKnight), EqualsBitboard(
                    "8: . X . . . . X ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kBlack, kBishop), EqualsBitboard(
                    "8: . . X . . X . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kBlack, kRook), EqualsBitboard(
                    "8: X . . . . . . X"
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kBlack, kQueen), EqualsBitboard(
                    "8: . . . X . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(position.GetPieces(kBlack, kKing), EqualsBitboard(
                    "8: . . . . X . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GetAttackers, Pawn) {
    Position position = MakePosition(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: . . p p p p p ."
            "4: . . P . . . P ."
            "3: . . P P P P P ."
            "2: . . . . . . . ."
            "1: . . . . . . . ."
            "   a b c d e f g h"
            //
            "   w KQkq - 0 1"
            );

    EXPECT_THAT(position.GetAttackers(E4), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . X . X . ."
                    "4: . . . . . . . ."
                    "3: . . . X . X . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GetAttackers, Rook) {
    //
    {
        Position position = MakePosition(
                "8: . . . r . . . ."
                "7: . . . . . . . ."
                "6: . . . . . . . ."
                "5: . . . . . . . ."
                "4: . . . . . . . ."
                "3: . . . . . . . ."
                "2: . . . . . . . ."
                "1: . r r . . r . ."
                "   a b c d e f g h"
                //
                "   w KQkq - 0 1"
                );

        EXPECT_THAT(position.GetAttackers(D1), EqualsBitboard(
                        "8: . . . X . . . ."
                        "7: . . . . . . . ."
                        "6: . . . . . . . ."
                        "5: . . . . . . . ."
                        "4: . . . . . . . ."
                        "3: . . . . . . . ."
                        "2: . . . . . . . ."
                        "1: . . X . . X . ."
                        "   a b c d e f g h"
                    ));
    }
    //
    {
        Position position = MakePosition(
                "8: . . . r . . . ."
                "7: . R . r . . . ."
                "6: . . . R . . . ."
                "5: . . . . . . . ."
                "4: R R R . . r R r"
                "3: . . . r . . . ."
                "2: . . . R . . r ."
                "1: . . . r . . . ."
                "   a b c d e f g h"
                //
                "   w KQkq - 0 1"
                );

        EXPECT_THAT(position.GetAttackers(D4), EqualsBitboard(
                        "8: . . . . . . . ."
                        "7: . . . . . . . ."
                        "6: . . . X . . . ."
                        "5: . . . . . . . ."
                        "4: . . X . . X . ."
                        "3: . . . X . . . ."
                        "2: . . . . . . . ."
                        "1: . . . . . . . ."
                        "   a b c d e f g h"
                    ));
    }
}

TEST(GetAttackers, Bishop) {
    Position position = MakePosition(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . b . . . B . ."
            "5: . . . . . . . ."
            "4: . . . . . . . ."
            "3: . . . . . . . ."
            "2: . B . . . b . ."
            "1: B . . . . . . ."
            "   a b c d e f g h"
            //
            "   w KQkq - 0 1"
            );

    EXPECT_THAT(position.GetAttackers(D4), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . X . . . X . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . X . . . X . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GetAttackers, Queen) {
    Position position = MakePosition(
            "8: . . . Q . . . Q"
            "7: . . . . . . B ."
            "6: . q . . . q . ."
            "5: . . . r . . . ."
            "4: Q . n . . . . q"
            "3: . . . . . . . ."
            "2: . . R . q . . ."
            "1: Q . . . . . . ."
            "   a b c d e f g h"
            //
            "   w KQkq - 0 1"
            );

    EXPECT_THAT(position.GetAttackers(D4), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . X . . . X . ."
                    "5: . . . X . . . ."
                    "4: . . . . . . . X"
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: X . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GetAttackers, Knight) {
    Position position = MakePosition(
            "8: . . . . . . . ."
            "7: . . . . . . . ."
            "6: . . . n . N . ."
            "5: . . N . . . n ."
            "4: . . . . . . . ."
            "3: . . N . . . N ."
            "2: . . . N . n . ."
            "1: . . . . . . . ."
            "   a b c d e f g h"
            //
            "   w KQkq - 0 1"
            );

    EXPECT_THAT(position.GetAttackers(E4), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . X . X . ."
                    "5: . . X . . . X ."
                    "4: . . . . . . . ."
                    "3: . . X . . . X ."
                    "2: . . . X . X . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GetAttackers, King) {
    Position position = MakePosition(
            "8: . K . . . . . ."
            "7: . . . . . . . ."
            "6: . . . . . . . ."
            "5: . . . K k K . ."
            "4: . . . k . K . ."
            "3: . . . k K k . ."
            "2: . . . . . . . ."
            "1: . k . . . . . ."
            "   a b c d e f g h"
            //
            "   w KQkq - 0 1"
            );

    EXPECT_THAT(position.GetAttackers(E4), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . X X X . ."
                    "4: . . . X . X . ."
                    "3: . . . X X X . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

} // namespace
} // namespace chessengine
