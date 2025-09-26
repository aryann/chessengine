load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_library(
    name = "bitboard",
    srcs = ["bitboard.cc"],
    hdrs = ["bitboard.h"],
    deps = [],
)

cc_test(
    name = "bitboard_test",
    srcs = ["bitboard_test.cc"],
    deps = [
        ":bitboard",
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
    ],
)

cc_library(
    name = "types",
    srcs = [],
    hdrs = ["types.h"],
    deps = [],
)
