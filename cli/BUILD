cc_binary(
    name = "chessengine",
    srcs = ["chessengine.cc"],
    deps = [
        ":command",
        "//:move_generator",
        "//:perft",
        "//:position",
        "//cli/commands:display",
        "//cli/commands:perft_command",
        "//cli/commands:position_command",
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "command",
    srcs = ["command.cc"],
    hdrs = ["command.h"],
    deps = [
        "//:perft",
        "//:position",
        "@abseil-cpp//absl/strings",
    ],
)
