cc_binary(
    name = "chessengine",
    srcs = ["chessengine.cc"],
    deps = [
        ":command",
        "//cli/commands:display",
        "//cli/commands:perft_command",
        "//cli/commands:position_command",
        "//engine:move_generator",
        "//engine:perft",
        "//engine:position",
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "command",
    srcs = ["command.cc"],
    hdrs = ["command.h"],
    visibility = [
        "//cli/commands:__subpackages__",
    ],
    deps = [
        "//engine:perft",
        "//engine:position",
        "@abseil-cpp//absl/strings",
    ],
)
