# chessengine

## Building

```shell
cmake --preset debug
cmake --build --preset debug
```

[bitboard_test.cc](engine/bitboard_test.cc)

## Running Tests

```shell[bitboard_test.cc](engine/bitboard_test.cc)
GTEST_COLOR=1 ctest --preset debug
```
