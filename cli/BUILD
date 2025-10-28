cc_binary(
    name = "chessengine",
    srcs = ["chessengine.cc"],
    deps = [
        ":command",
        "//:move_generator",
        "//:perft",
        "//:position",
        "//cli/commands:display",
        "//cli/commands:perft",
        "//cli/commands:position",
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "command",
    srcs = [],
    hdrs = ["command.h"],
    deps = [
        "//:perft",
        "//:position",
        "@abseil-cpp//absl/strings",
    ],
)
