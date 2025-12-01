#add_library(chessengine_commands)
#
#target_sources(chessengine_commands
#        PRIVATE
#        position_command.cc
#
#        PUBLIC
#        FILE_SET HEADERS
#        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.."
#        FILES
#        display.h
#        isready_command.h
#        perft_command.h
#        position_command.h
#        uci_command.h
#)
#
#target_link_libraries(chessengine_commands)