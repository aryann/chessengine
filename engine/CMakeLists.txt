add_library(engine)

target_sources(
        engine

        PRIVATE
        bitboard.cc

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.."
        FILES
        bitboard.h
        types.h
)

target_link_libraries(
        engine
        absl::log
)

target_compile_features(engine PRIVATE cxx_std_23)
