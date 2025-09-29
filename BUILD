load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_library(
    name = "attacks",
    srcs = [],
    hdrs = ["attacks.h"],
    deps = [
        ":bitboard",
    ],
)

cc_binary(
    name = "attacks_main",
    srcs = ["attacks_main.cc"],
    deps = [":attacks"],
)

cc_test(
    name = "attacks_test",
    srcs = ["attacks_test.cc"],
    deps = [
        ":attacks",
        ":testing",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "bitboard",
    srcs = ["bitboard.cc"],
    hdrs = ["bitboard.h"],
    deps = [
        ":types",
    ],
)

cc_test(
    name = "bitboard_test",
    srcs = ["bitboard_test.cc"],
    deps = [
        ":bitboard",
        ":testing",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "position",
    srcs = ["position.cc"],
    hdrs = ["position.h"],
    deps = [
        ":bitboard",
        ":types",
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "move",
    srcs = ["move.cc"],
    hdrs = ["move.h"],
    deps = [
        ":types",
    ],
)

cc_test(
    name = "move_test",
    srcs = ["move_test.cc"],
    deps = [
        ":move",
        "@googletest//:gtest",
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
        "@abseil-cpp//absl/strings",
        "@googletest//:gtest",
    ],
)

cc_library(
    name = "types",
    srcs = [],
    hdrs = ["types.h"],
    deps = [],
)
