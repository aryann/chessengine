add_library(chessengine_search STATIC)

target_sources(chessengine_search
        PRIVATE
        evaluation.cc
        evaluation.h
        move_ordering.cc
        move_ordering.h
        transposition.h
        search.cc

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.."
        FILES search.h
)

target_link_libraries(chessengine_search
        PUBLIC
        chessengine_engine

        PRIVATE
        absl::flat_hash_map
)

###############################################################################
# Tests:
###############################################################################
include(GoogleTest)

function(make_test TEST_NAME)
    add_executable(${TEST_NAME} "${TEST_NAME}.cc")

    target_link_libraries(${TEST_NAME}
            PRIVATE
            chessengine_search
            chessengine_testing
            GTest::gtest_main
    )
    gtest_discover_tests(${TEST_NAME})
endfunction()

make_test(evaluation_test)
make_test(move_ordering_test)
make_test(search_test)