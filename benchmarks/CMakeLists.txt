#function(add_benchmark NAME)
#    add_executable(${NAME} "${NAME}_benchmark.cc")
#
#    target_link_libraries(${NAME}
#            PRIVATE
#            chessengine_engine
#            benchmark::benchmark_main
#    )
#
#    if (ARGN)
#        # Pass optional dependencies:
#        target_link_libraries(${NAME} PRIVATE ${ARGN})
#    endif ()
#
#endfunction()
#
#add_benchmark(attacks)
#add_benchmark(moves)
#add_benchmark(search)
