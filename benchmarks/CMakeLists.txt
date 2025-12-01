function(add_benchmark NAME)
    add_executable(${NAME} "${NAME}_benchmark.cc")
    target_link_libraries(${NAME}
            PRIVATE
            benchmark::benchmark_main
            ${ARGN}
    )
endfunction()

add_benchmark(attacks chessengine_engine)
add_benchmark(moves chessengine_engine)
add_benchmark(search chessengine_search)
