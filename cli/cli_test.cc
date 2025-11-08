#include "cli.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace chessengine {
namespace {

using ::testing::Eq;
using ::testing::IsEmpty;

class CliTest : public ::testing::Test {
 protected:
  CliTest()
      : state_({.position = Position::Starting()}),
        command_dispatcher_(MakeCommandDispatcher(state_)),
        old_stdout_buffer_((std::cout.rdbuf())) {
    std::cout.rdbuf(stream_.rdbuf());
  }

  ~CliTest() override { std::cout.rdbuf(old_stdout_buffer_); }

  std::string GetOutput() const { return stream_.str(); }

  std::expected<void, std::string> Run(
      const std::vector<std::string_view>& command) {
    return command_dispatcher_.Run(command);
  }

 protected:
  CommandState state_;
  CommandDispatcher command_dispatcher_;

  std::stringstream stream_;
  std::streambuf* old_stdout_buffer_;
};

TEST_F(CliTest, IsReady) {
  ASSERT_THAT(Run({"isready"}).error_or(""), IsEmpty());
  EXPECT_THAT(GetOutput(), Eq("readyok\n"));
}

}  // namespace
}  // namespace chessengine