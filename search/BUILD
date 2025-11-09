package(
    default_visibility = [
        "//:__subpackages__",
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
