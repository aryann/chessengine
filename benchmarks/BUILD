cc_binary(
    name = "attacks_benchmark",
    srcs = ["attacks_benchmark.cc"],
    deps = [
        "//:attacks",
        "@google_benchmark//:benchmark",
    ],
)

cc_binary(
    name = "moves_benchmark",
    srcs = ["moves_benchmark.cc"],
    deps = [
        "//:move_generator",
        "//:position",
        "//:scoped_move",
        "//:types",
        "@google_benchmark//:benchmark",
    ],
)
