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

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

