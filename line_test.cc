#include "line.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "testing.h"

namespace chessengine {
namespace {

TEST(GetLine, Vertical) {
    EXPECT_THAT(GetLine(A1, A5), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: X . . . . . . ."
                    "3: X . . . . . . ."
                    "2: X . . . . . . ."
                    "1: X . . . . . . ."
                    "   a b c d e f g h"
                ));
    EXPECT_THAT(GetLine(H8, H3), EqualsBitboard(
                    "8: . . . . . . . X"
                    "7: . . . . . . . X"
                    "6: . . . . . . . X"
                    "5: . . . . . . . X"
                    "4: . . . . . . . X"
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GetLine(D8, D1), EqualsBitboard(
                    "8: . . . X . . . ."
                    "7: . . . X . . . ."
                    "6: . . . X . . . ."
                    "5: . . . X . . . ."
                    "4: . . . X . . . ."
                    "3: . . . X . . . ."
                    "2: . . . X . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GetLine, Horizontal) {
    EXPECT_THAT(GetLine(A1, E1), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: X X X X . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GetLine(H7, C7), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . X X X X X"
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GetLine(A4, H4), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: X X X X X X X ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GetLine, Diagonal) {
    EXPECT_THAT(GetLine(A1, H8), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . X ."
                    "6: . . . . . X . ."
                    "5: . . . . X . . ."
                    "4: . . . X . . . ."
                    "3: . . X . . . . ."
                    "2: . X . . . . . ."
                    "1: X . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GetLine(H1, A8), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . X . . . . . ."
                    "6: . . X . . . . ."
                    "5: . . . X . . . ."
                    "4: . . . . X . . ."
                    "3: . . . . . X . ."
                    "2: . . . . . . X ."
                    "1: . . . . . . . X"
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GetLine(C2, F5), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . X . . ."
                    "3: . . . X . . . ."
                    "2: . . X . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GetLine(B6, E3), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . X . . . . . ."
                    "5: . . X . . . . ."
                    "4: . . . X . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GetLine, EdgeCases) {
    EXPECT_THAT(GetLine(A1, A1), EqualsBitboard(kEmptyBoard));

    EXPECT_THAT(GetLine(D4, D5), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . X . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GetLine(G4, H4), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . X ."
                    "3: . . . . . . . ."
                    "2: . . . . . . . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));

    EXPECT_THAT(GetLine(F2, G3), EqualsBitboard(
                    "8: . . . . . . . ."
                    "7: . . . . . . . ."
                    "6: . . . . . . . ."
                    "5: . . . . . . . ."
                    "4: . . . . . . . ."
                    "3: . . . . . . . ."
                    "2: . . . . . X . ."
                    "1: . . . . . . . ."
                    "   a b c d e f g h"
                ));
}

TEST(GetLine, NotOnALine) {
    EXPECT_THAT(GetLine(A1, C2), EqualsBitboard(kEmptyBoard));
    EXPECT_THAT(GetLine(E4, H2), EqualsBitboard(kEmptyBoard));
    EXPECT_THAT(GetLine(H8, A2), EqualsBitboard(kEmptyBoard));
}

} // namespace
} // namespace chessengine
