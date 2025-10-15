#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "absl/strings/str_join.h"
#include "move.h"
#include "move_generator.h"
#include "position.h"

namespace chessengine {
namespace {

using ::testing::ElementsAreArray;
using ::testing::IsEmpty;

struct PerftTestCase {
    std::string name;
    std::string_view fen;
    std::vector<int> expected_node_counts;
};

void PrintTo(const PerftTestCase &test_case, std::ostream *os) {
    *os << "{ "
            << R"(.name = ")" << test_case.name << R"(")"
            << R"(, .fen = ")" << test_case.fen << R"(")"
            << ", .expected_node_counts = {"
            << absl::StrJoin(test_case.expected_node_counts, ", ") << "} "
            << "}";
}

class PerftTest : public testing::TestWithParam<PerftTestCase> {
protected:
    void RunPerft(std::size_t depth, Position &position, std::vector<int> &nodes) {
        ++nodes[nodes.size() - depth];

        if (depth <= 1) {
            return;
        }

        std::vector<Move> moves = GenerateMoves<kQuiet>(position);
        for (const Move &move: moves) {
            position.Do(move);
            RunPerft(depth - 1, position, nodes);
            position.Undo(move);
        }
    }
};

std::string GetTestName(const testing::TestParamInfo<PerftTestCase> &info) {
    return info.param.name;
}

TEST_P(PerftTest, Run) {
    const auto &[_, fen, expected_node_count] = GetParam();
    const std::size_t depth = expected_node_count.size();

    std::expected<Position, std::string> position = Position::FromFen(fen);
    ASSERT_THAT(position.error_or(""), IsEmpty());

    std::vector<int> nodes(depth);
    RunPerft(depth, position.value(), nodes);

    EXPECT_THAT(nodes, ElementsAreArray(expected_node_count));
}

INSTANTIATE_TEST_SUITE_P(
        Perft,
        PerftTest,
        testing::Values(
            // https://www.chessprogramming.org/Perft_Results#Initial_Position
            PerftTestCase{
            .name = "StartingPosition",
            .fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
            .expected_node_counts = {1, 20, 400},
            },

            // https: //www.chessprogramming.org/Perft_Results#Position_2
            PerftTestCase{
            .name = "Position10",
            .fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1",

            // TODO(aryann): This is wrong. Fix this once the move generator can
            // correctly generate all moves.
            .expected_node_counts = {1, 38, 1267, 48155},
            },

            // https: //www.chessprogramming.org/Perft_Results#Position_3
            PerftTestCase{
            .name = "position10",
            .fen = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1",

            // TODO(aryann): This is wrong. Fix this once the move generator can
            // correctly generate all moves.
            .expected_node_counts = {1, 15, 239, 3754},
            }
        ),
        GetTestName);

} // namespace
} // namespace chessengine
