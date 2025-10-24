#include "move.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::IsEmpty;
using ::testing::IsTrue;
using ::testing::IsFalse;
using ::testing::Ne;
using ::testing::Not;

TEST(Move, NonPromotion) {
    Move move(A1, B2);

    EXPECT_THAT(move.from(), Eq(A1));
    EXPECT_THAT(move.to(), Eq(B2));
    EXPECT_THAT(move.IsPromotion(), IsFalse());
}

TEST(Move, Promotion) {
    //
    {
        Move move(A7, A8, kKnight);

        EXPECT_THAT(move.from(), Eq(A7));
        EXPECT_THAT(move.to(), Eq(A8));
        EXPECT_THAT(move.IsPromotion(), IsTrue());
        EXPECT_THAT(move.GetPromotedPiece(), Eq(kKnight));
    }
    //
    {
        Move move(A7, A8, kBishop);

        EXPECT_THAT(move.from(), Eq(A7));
        EXPECT_THAT(move.to(), Eq(A8));
        EXPECT_THAT(move.IsPromotion(), IsTrue());
        EXPECT_THAT(move.GetPromotedPiece(), Eq(kBishop));
    }
    //
    {
        Move move(A7, A8, kRook);

        EXPECT_THAT(move.from(), Eq(A7));
        EXPECT_THAT(move.to(), Eq(A8));
        EXPECT_THAT(move.IsPromotion(), IsTrue());
        EXPECT_THAT(move.GetPromotedPiece(), Eq(kRook));
    }
    //
    {
        Move move(A7, A8, kQueen);

        EXPECT_THAT(move.from(), Eq(A7));
        EXPECT_THAT(move.to(), Eq(A8));
        EXPECT_THAT(move.IsPromotion(), IsTrue());
        EXPECT_THAT(move.GetPromotedPiece(), Eq(kQueen));
    }
}

TEST(Move, Equality) {
    EXPECT_THAT(Move(A1, A2), Eq(Move(A1, A2)));
    EXPECT_THAT(Move(A7, A8, kKnight), Eq(Move(A7, A8, kKnight)));
    EXPECT_THAT(Move(A7, A8, kKnight), Not(Eq(Move(A7, A8, kBishop))));
    EXPECT_THAT(Move(A1, A2), Not(Eq(Move(H1, H2))));

    EXPECT_THAT(Move(A1, A2), Not(Ne(Move(A1, A2))));
    EXPECT_THAT(Move(A1, A2), Ne(Move(H1, H2)));
}

TEST(FromUCI, Valid) {
    //
    {
        std::expected<Move, std::string> move = Move::FromUCI("e2e4");
        ASSERT_THAT(move.error_or(""), IsEmpty());
        EXPECT_THAT(move->from(), Eq(E2));
        EXPECT_THAT(move->to(), Eq(E4));
        EXPECT_THAT(move->IsCastling(), IsFalse());
        EXPECT_THAT(move->IsPromotion(), IsFalse());
    }
    //
    {
        std::expected<Move, std::string> move = Move::FromUCI("e1g1n");
        ASSERT_THAT(move.error_or(""), IsEmpty());
        EXPECT_THAT(move->from(), Eq(E1));
        EXPECT_THAT(move->to(), Eq(G1));
        EXPECT_THAT(move->IsCastling(), IsFalse());
        ASSERT_THAT(move->IsPromotion(), IsTrue());
        EXPECT_THAT(move->GetPromotedPiece(), Eq(kKnight));
    }
    //
    {
        std::expected<Move, std::string> move = Move::FromUCI("e1g1b");
        ASSERT_THAT(move.error_or(""), IsEmpty());
        EXPECT_THAT(move->IsCastling(), IsFalse());
        ASSERT_THAT(move->IsPromotion(), IsTrue());
        EXPECT_THAT(move->GetPromotedPiece(), Eq(kBishop));
    }
    //
    {
        std::expected<Move, std::string> move = Move::FromUCI("e1g1r");
        ASSERT_THAT(move.error_or(""), IsEmpty());
        EXPECT_THAT(move->IsCastling(), IsFalse());
        ASSERT_THAT(move->IsPromotion(), IsTrue());
        EXPECT_THAT(move->GetPromotedPiece(), Eq(kRook));
    }
    //
    {
        std::expected<Move, std::string> move = Move::FromUCI("e1g1q");
        ASSERT_THAT(move.error_or(""), IsEmpty());
        EXPECT_THAT(move->IsCastling(), IsFalse());
        ASSERT_THAT(move->IsPromotion(), IsTrue());
        EXPECT_THAT(move->GetPromotedPiece(), Eq(kQueen));
    }
    //
    {
        std::expected<Move, std::string> move = Move::FromUCI("e1c1#c");
        ASSERT_THAT(move.error_or(""), IsEmpty());
        EXPECT_THAT(move->IsCastling(), IsTrue());
        EXPECT_THAT(move->IsPromotion(), IsFalse());
    }
}

TEST(FromUCI, Invalid) {
    EXPECT_THAT(Move::FromUCI("").error_or(""), Eq("Invalid UCI move: "));
    EXPECT_THAT(Move::FromUCI("e1").error_or(""), Eq("Invalid UCI move: e1"));
    EXPECT_THAT(Move::FromUCI("e1e").error_or(""), Eq("Invalid UCI move: e1e"));
    EXPECT_THAT(Move::FromUCI("e1e2invalid").error_or(""), Eq("Invalid UCI move: e1e2invalid"));
    EXPECT_THAT(Move::FromUCI("e7e8k").error_or(""), Eq("Invalid UCI move: e7e8k"));
    EXPECT_THAT(Move::FromUCI("e7e8p").error_or(""), Eq("Invalid UCI move: e7e8p"));
    EXPECT_THAT(Move::FromUCI("e7e8#ccc").error_or(""), Eq("Invalid UCI move: e7e8#ccc"));

}

TEST(Move, String) {
    auto ToString = [](const Move &move) {
        std::stringstream buf;
        buf << move;
        return buf.str();
    };

    EXPECT_THAT(ToString(Move(E7, E5)), Eq("e7e5"));
    EXPECT_THAT(ToString(Move(G2, G1, kKnight)), Eq("g2g1n"));
    EXPECT_THAT(ToString(Move(G2, G1, kBishop)), Eq("g2g1b"));
    EXPECT_THAT(ToString(Move(G2, G1, kRook)), Eq("g2g1r"));
    EXPECT_THAT(ToString(Move(G2, G1, kQueen)), Eq("g2g1q"));

    EXPECT_THAT(ToString(Move(E1, G1, Move::Flags::kCastle)), Eq("e1g1#c"));
}

} // namespace
} // namespace chessengine
