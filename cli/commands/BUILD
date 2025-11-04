cc_library(
    name = "display",
    srcs = [],
    hdrs = ["display.h"],
    visibility = [
        "//cli:__subpackages__",
    ],
    deps = [
        "//cli:command",
        "//engine:perft",
        "//engine:position",
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "perft_command",
    srcs = [],
    hdrs = ["perft_command.h"],
    visibility = [
        "//cli:__subpackages__",
    ],
    deps = [
        "//cli:command",
        "//engine:perft",
        "//engine:position",
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "position_command",
    srcs = ["position_command.cc"],
    hdrs = ["position_command.h"],
    visibility = [
        "//cli:__subpackages__",
    ],
    deps = [
        "//cli:command",
        "//engine:move",
        "//engine:perft",
        "//engine:position",
        "@abseil-cpp//absl/strings",
    ],
)
