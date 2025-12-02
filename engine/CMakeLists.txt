###############################################################################
# Primitives:
###############################################################################

add_library(chessengine_primitives)

target_sources(chessengine_primitives
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
        bitboard.ccm
        magic.ccm
        types.ccm
)

target_link_libraries(chessengine_primitives
        PUBLIC
        absl::log
        absl::check
)

target_compile_features(chessengine_primitives PUBLIC cxx_std_23)

###############################################################################
# Magic bitboard generation:
###############################################################################

add_executable(generate_magic)

target_sources(generate_magic
        PRIVATE
        magic_main.cc
)

target_link_libraries(generate_magic
        PRIVATE
        chessengine_primitives
        absl::log
)

set(MAGIC_HEADER_PATH "${CMAKE_CURRENT_BINARY_DIR}/magic.generated.h")

add_custom_command(
        OUTPUT ${MAGIC_HEADER_PATH}
        COMMAND generate_magic ${MAGIC_HEADER_PATH}
        DEPENDS generate_magic
        VERBATIM
)

add_custom_target(run_generate_magic DEPENDS ${MAGIC_HEADER_PATH})

add_library(chessengine_magic INTERFACE)

target_sources(chessengine_magic
        INTERFACE
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/.."
        FILES ${MAGIC_HEADER_PATH}
)

add_dependencies(chessengine_magic
        run_generate_magic
)

###############################################################################
# Core engine library:
###############################################################################

add_library(chessengine_engine)

target_sources(chessengine_engine
        PRIVATE
        game.cc
        move_generator.cc
        move.cc
        perft.cc
        position.cc

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.."
        FILES
        attacks.h
        castling.h
        game.h
        line.h
        #magic.ccm
        move_generator.h
        move.h
        perft.h
        position.h
        scoped_move.h
        zobrist.h
)

target_link_libraries(chessengine_engine
        PUBLIC
        chessengine_primitives
        chessengine_magic

        PRIVATE
        absl::check
        absl::log
)

target_compile_features(chessengine_engine PRIVATE cxx_std_23)

###############################################################################
# Testing library:
###############################################################################

add_library(chessengine_testing)

target_sources(chessengine_testing
        PRIVATE
        testing.cc

        PUBLIC FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.."
        FILES testing.h
)

target_link_libraries(chessengine_testing
        PUBLIC
        chessengine_engine
        GTest::gmock
        absl::strings
)

target_compile_features(chessengine_testing PRIVATE cxx_std_23)

###############################################################################
# Tests:
###############################################################################

include(GoogleTest)

function(make_test TEST_NAME)
    add_executable(${TEST_NAME} "${TEST_NAME}.cc")
    target_link_libraries(${TEST_NAME}
            PRIVATE
            chessengine_testing
            GTest::gtest_main
            chessengine_magic
    )
    gtest_discover_tests(${TEST_NAME})
endfunction()

make_test(attacks_test)
make_test(bitboard_test)
make_test(castling_test)
make_test(game_test)
make_test(line_test)
make_test(move_generator_test)
make_test(move_test)
make_test(perft_test)
make_test(position_test)
make_test(testing_test)
make_test(types_test)
make_test(zobrist_test)
