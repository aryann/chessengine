package(
    default_visibility = [
        "//:__subpackages__",
    ],
)

cc_library(
    name = "evaluation",
    srcs = ["evaluation.cc"],
    hdrs = ["evaluation.h"],
    deps = [
        "//engine:move",
        "//engine:move_generator",
        "//engine:position",
        "//engine:scoped_move",
        "//engine:types",
    ],
)

cc_test(
    name = "evaluation_test",
    srcs = ["evaluation_test.cc"],
    deps = [
        ":evaluation",
        "//engine:position",
        "//engine:testing",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "search",
    srcs = [],
    hdrs = ["search.h"],
    deps = [
        "//engine:move",
        "//engine:position",
    ],
)

cc_library(
    name = "random_search",
    srcs = ["random_search.cc"],
    hdrs = ["random_search.h"],
    deps = [
        "//engine:move",
        "//engine:move_generator",
        "//engine:position",
        "//engine:scoped_move",
        "//engine:types",
    ],
)
