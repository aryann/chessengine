cc_binary(
    name = "chessengine",
    srcs = ["chessengine.cc"],
    deps = [
        ":cli",
        ":command",
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "cli",
    srcs = ["cli.cc"],
    hdrs = ["cli.h"],
    deps = [
        ":command",
        "//cli/commands:display",
        "//cli/commands:isready_command",
        "//cli/commands:perft_command",
        "//cli/commands:position_command",
        "//cli/commands:uci_command",
        "//engine:game",
        "//engine:move_generator",
        "//engine:perft",
        "//engine:position",
        "@abseil-cpp//absl/strings",
    ],
)

cc_test(
    name = "cli_test",
    srcs = ["cli_test.cc"],
    deps = [
        ":cli",
        "//engine:position",
        "@abseil-cpp//absl/strings",
        "@googletest//:gtest_main",
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
