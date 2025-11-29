cmake_minimum_required(VERSION 3.23)

project(chessengine)

if ((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR
(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))
    add_compile_options(/W4)

elseif ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR
(CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(-Wall -Werror)

endif ()

add_subdirectory(engine)
add_subdirectory(third_party/abseil-cpp EXCLUDE_FROM_ALL)
