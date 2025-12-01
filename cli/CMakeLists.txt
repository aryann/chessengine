###############################################################################
# Commands:
###############################################################################

add_library(chessengine_commands STATIC)

target_sources(chessengine_commands
        # Source files (Implementations)
        PRIVATE
        command.cc
        commands/position_command.cc
        # Note: display, perft, etc. had empty srcs=[] in Bazel,
        # so we assume they are header-only or inline.

        # Public Headers
        # We set BASE_DIRS to ".." so consumers include them as "cli/command.h"
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.."
        FILES
        command.h
        commands/display.h
        commands/isready_command.h
        commands/perft_command.h
        commands/position_command.h
        commands/uci_command.h
)

target_link_libraries(chessengine_commands
        PUBLIC
        chessengine_engine
        chessengine_search
        absl::strings
)

target_compile_features(chessengine_commands PRIVATE cxx_std_23)

###############################################################################
# Command-Line Interface (CLI):
###############################################################################

add_library(chessengine_cli STATIC)

target_sources(chessengine_cli
        PRIVATE
        cli.cc

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.."
        FILES
        cli.h
)

target_link_libraries(chessengine_cli
        PUBLIC
        chessengine_commands
        chessengine_engine
)

target_compile_features(chessengine_cli PRIVATE cxx_std_23)

###############################################################################
# Main executable:
###############################################################################

add_executable(chessengine)

target_sources(chessengine
        PRIVATE
        chessengine.cc
)

target_link_libraries(chessengine
        PRIVATE
        absl::strings
        chessengine_cli
)

###############################################################################
# Tests:
###############################################################################

include(GoogleTest)

add_executable(cli_test)

target_sources(cli_test
        PRIVATE
        cli_test.cc)


target_link_libraries(cli_test
        PRIVATE
        chessengine_cli
        GTest::gmock
        GTest::gtest_main
)

gtest_discover_tests(cli_test)
