###############################################################################
# Magic bitboard generation:
###############################################################################

add_executable(generate_magic)

target_sources(generate_magic
        PRIVATE
        magic_main.cc
        types.cc

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.."
        FILES
        magic.h
        bitboard.h
        types.h
)

target_link_libraries(generate_magic
        absl::log
)

set(MAGIC_HEADER_PATH "${CMAKE_CURRENT_BINARY_DIR}/magic.generated.h")

add_custom_command(
        OUTPUT ${MAGIC_HEADER_PATH}
        COMMAND generate_magic ${MAGIC_HEADER_PATH}
        DEPENDS generate_magic
        VERBATIM
)

add_custom_target(RunGenerateMagic DEPENDS ${MAGIC_HEADER_PATH})

add_library(magic INTERFACE)

target_sources(magic
        INTERFACE
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/.."
        FILES ${MAGIC_HEADER_PATH}
)

add_dependencies(magic
        RunGenerateMagic
)

###############################################################################
# Core engine library:
###############################################################################

add_library(engine)

target_sources(engine
        PRIVATE
        bitboard.cc
        game.cc
        move_generator.cc
        move.cc
        perft.cc
        position.cc
        types.cc

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.."
        FILES
        attacks.h
        bitboard.h
        castling.h
        game.h
        line.h
        magic.h
        move_generator.h
        move.h
        perft.h
        position.h
        scoped_move.h
        types.h
        zobrist.h
)

target_link_libraries(engine
        PUBLIC
        absl::check
        absl::log
        magic
)

target_compile_features(engine PRIVATE cxx_std_23)

###############################################################################
# Testing library:
###############################################################################

add_library(testing)

target_sources(testing
        PRIVATE
        testing.cc

        PUBLIC FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.."
        FILES testing.h
)

target_link_libraries(testing
        PUBLIC
        engine
        GTest::gmock
        absl::strings)

target_compile_features(testing PRIVATE cxx_std_23)

###############################################################################
# Tests:
###############################################################################

include(GoogleTest)

macro(make_test TEST_NAME)
    add_executable(${TEST_NAME} "${TEST_NAME}.cc")
    target_link_libraries(${TEST_NAME}
            PRIVATE
            testing
            GTest::gtest_main
    )
    gtest_discover_tests(${TEST_NAME})
endmacro()

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
