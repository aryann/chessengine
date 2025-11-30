# chessengine

## Building

```shell
cmake --preset main # --fresh
cmake --build build2
```

## Running Tests

```shell
GTEST_COLOR=1 ctest --test-dir build2/engine --output-on-failure
```
