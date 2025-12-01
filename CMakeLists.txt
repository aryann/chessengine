cmake_minimum_required(VERSION 3.23)

project(chessengine)

if ((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR
(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))
    add_compile_options(/W4)

elseif ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR
(CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(-Wall -Werror)

endif ()

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppress benchmark tests." FORCE)

# N.B.: third_party/benchmark depends on third_party/googletest, so
# third_party/googletest must be added first.
add_subdirectory(third_party/abseil-cpp EXCLUDE_FROM_ALL)
add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)
add_subdirectory(third_party/benchmark EXCLUDE_FROM_ALL)

enable_testing()

add_subdirectory(benchmarks)
add_subdirectory(cli)
add_subdirectory(engine)
add_subdirectory(search)
