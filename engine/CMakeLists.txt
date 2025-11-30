add_library(engine)

target_sources(engine
        PRIVATE
        bitboard.cc
        game.cc
        magic_main.cc
        move_generator.cc
        move.cc
        perft.cc
        position_main.cc
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
        absl::log
)

target_compile_features(engine PRIVATE cxx_std_23)

add_library(testing)
target_sources(testing
        PRIVATE
        testing.cc

        PUBLIC FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.."
        FILES testing.h
)
target_link_libraries(testing
        PRIVATE
        engine
        GTest::gtest
        GTest::gmock
        absl::strings)
target_compile_features(testing
        PRIVATE cxx_std_23)

enable_testing()

add_executable(bitboard_test)
target_sources(bitboard_test
        PRIVATE
        bitboard_test.cc)
target_link_libraries(bitboard_test
        PRIVATE
        engine
        testing
        GTest::gmock
        GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(bitboard_test)
