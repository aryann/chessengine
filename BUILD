load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_library(
    name = "attacks",
    srcs = [],
    hdrs = ["attacks.h"],
    deps = [
        ":bitboard",
        "@abseil-cpp//absl/log:check",
    ],
)

cc_test(
    name = "attacks_test",
    srcs = ["attacks_test.cc"],
    deps = [
        ":attacks",
        ":testing",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "bitboard",
    srcs = ["bitboard.cc"],
    hdrs = ["bitboard.h"],
    deps = [
        ":types",
        "@abseil-cpp//absl/log:check",
    ],
)

cc_test(
    name = "bitboard_test",
    srcs = ["bitboard_test.cc"],
    deps = [
        ":bitboard",
        ":testing",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "castling",
    srcs = [],
    hdrs = ["castling.h"],
    deps = [
        ":bitboard",
        ":types",
    ],
)

cc_test(
    name = "castling_test",
    srcs = ["castling_test.cc"],
    deps = [
        ":castling",
        ":testing",
        "@googletest//:gtest_main",
    ],
)

cc_binary(
    name = "chessengine",
    srcs = ["chessengine.cc"],
    deps = [
        ":perft",
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "line",
    srcs = [],
    hdrs = ["line.h"],
    deps = [
        ":bitboard",
        ":types",
        "@abseil-cpp//absl/log:check",
    ],
)

cc_test(
    name = "line_test",
    srcs = ["line_test.cc"],
    deps = [
        ":line",
        ":testing",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "position",
    srcs = ["position.cc"],
    hdrs = ["position.h"],
    deps = [
        ":attacks",
        ":bitboard",
        ":castling",
        ":move",
        ":types",
        "@abseil-cpp//absl/log:check",
        "@abseil-cpp//absl/strings",
    ],
)

cc_test(
    name = "position_test",
    srcs = ["position_test.cc"],
    deps = [
        ":position",
        ":scoped_move",
        ":testing",
        "@googletest//:gtest_main",
    ],
)

cc_binary(
    name = "position_main",
    srcs = ["position_main.cc"],
    deps = [
        ":position",
    ],
)

cc_library(
    name = "scoped_move",
    srcs = [],
    hdrs = ["scoped_move.h"],
    deps = [
        ":move",
        ":position",
    ],
)

cc_library(
    name = "move",
    srcs = ["move.cc"],
    hdrs = ["move.h"],
    deps = [
        ":castling",
        ":types",
        "@abseil-cpp//absl/log:check",
    ],
)

cc_test(
    name = "move_test",
    srcs = ["move_test.cc"],
    deps = [
        ":move",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "perft",
    srcs = ["perft.cc"],
    hdrs = ["perft.h"],
    deps = [
        ":move",
        ":move_generator",
        ":position",
        ":scoped_move",
    ],
)

cc_test(
    name = "perft_test",
    srcs = ["perft_test.cc"],
    shard_count = 8,
    deps = [
        ":move",
        ":move_generator",
        ":perft",
        ":position",
        "@abseil-cpp//absl/strings",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "move_generator",
    srcs = ["move_generator.cc"],
    hdrs = ["move_generator.h"],
    deps = [
        ":attacks",
        ":line",
        ":move",
        ":position",
        ":types",
    ],
)

cc_test(
    name = "move_generator_test",
    srcs = ["move_generator_test.cc"],
    deps = [
        ":move_generator",
        ":position",
        ":testing",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "testing",
    testonly = True,
    srcs = ["testing.cc"],
    hdrs = ["testing.h"],
    deps = [
        ":bitboard",
        ":position",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
        "@abseil-cpp//absl/strings",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "testing_test",
    srcs = ["testing_test.cc"],
    deps = [
        ":testing",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "types",
    srcs = ["types.cc"],
    hdrs = ["types.h"],
    deps = [
        "@abseil-cpp//absl/log:check",
        "@abseil-cpp//absl/strings:str_format",
    ],
)

cc_test(
    name = "types_test",
    srcs = ["types_test.cc"],
    deps = [
        ":testing",
        ":types",
        "@googletest//:gtest_main",
    ],
)
