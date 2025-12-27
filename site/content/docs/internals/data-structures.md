---
title: "Data Structures"
summary: ""
date: 2025-12-27T03:07:22.223+00:00
lastmod: 2025-12-27T03:07:22.223+00:00
draft: false
weight: 910
toc: true
seo:
  title: "" # custom title (optional)
  description: "" # custom description (recommended)
---

This guide describes the core data structures used within the FollyChess
implementation. It is intended for developers interested in the engine's
internals. We assume familiarity with C++.

## Bitboards

A key requirement for any chess engine is an efficient way to track square
occupancy. FollyChess uses bitboards: unsigned 64-bit integers where each bit
maps to one of the 64 chess squares.

FollyChess maps bits to squares by following a top-to-bottom, left-to-right
progression, which matches the typical visual representation of a chessboard.
The `A8` square corresponds to the least
significant bit (LSB), and `H1` to the most significant bit (MSB).

```text
8:   0   1   2   3   4   5   6   7
7:   8   9  10  11  12  13  14  15
6:  16  17  18  19  20  21  22  23
5:  24  25  26  27  28  29  30  31
4:  32  33  34  35  36  37  38  39
3:  40  41  42  43  44  45  46  47
2:  48  49  50  51  52  53  54  55
1:  56  57  58  59  60  61  62  63
    a   b   c   d   e   f   g   h
```

### Examples

* `1ULL`: Represents only the `A8` square.
* `3ULL` (`0b11`): Represents the `A8` and `B8` squares.
* `1ULL << 63`: Represents only the `H1` square.

## The Bitboard Class

The [Bitboard](https://github.com/aryann/follychess/blob/main/engine/bitboard.h)
class encapsulates the underlying unsigned 64-bit integer and provides a clean
API for bitwise manipulation: By using `constexpr`, we ensure many board
calculations are inlined by the compiler.

```cpp
class Bitboard {
 public:
  constexpr explicit Bitboard(std::uint64_t data) : data_(data) {}

  constexpr Bitboard operator&(const Bitboard &other) const {
    return Bitboard(data_ & other.data_);
  }

  constexpr Bitboard operator&(Square square) const {
    return Bitboard(data_ & (1ULL << square));
  }

  constexpr Bitboard operator<<(int bits) const {
    return Bitboard(data_ << bits);
  }

  constexpr Bitboard operator>>(int bits) const {
    return Bitboard(data_ >> bits);
  }

  // ...

 private:
  std::uint64_t data_;
};
```

## The Square Enum

The `Square` enum provides a named constant for every square, making the code
more readable:

```cpp
enum Square : std::uint8_t {
  A8, B8, C8, D8, E8, F8, G8, H8,
  A7, B7, C7, D7, E7, F7, G7, H7,
  A6, B6, C6, D6, E6, F6, G6, H6,
  A5, B5, C5, D5, E5, F5, G5, H5,
  A4, B4, C4, D4, E4, F4, G4, H4,
  A3, B3, C3, D3, E3, F3, G3, H3,
  A2, B2, C2, D2, E2, F2, G2, H2,
  A1, B1, C1, D1, E1, F1, G1, H1,
};
```

The Bitboard class provides facilities for working with squares:

```cpp
class Bitboard {
 public:
  // Initializes a bitboard with a single square set.
  constexpr explicit Bitboard(Square square) : data_(1ULL << square) {}

  // Gets the square of the least significant bit (LSB).
  //
  // Precondition: The Bitboard must not be empty.
  [[nodiscard]] constexpr Square LeastSignificantBit() const {
    if !consteval {
      DCHECK(data_ != 0ULL);
    }
    return static_cast<Square>(std::countr_zero(data_));
  }

  // Finds the least significant bit (LSB), clears it from the board,
  // and returns its corresponding square.
  //
  // Precondition: The Bitboard must not be empty.
  constexpr Square PopLeastSignificantBit() {
    Square square = LeastSignificantBit();
    data_ &= data_ - 1;
    return square;
  }

  // ...
};
```

Example:

```cpp
Bitboard pieces = ...
while (pieces) {
  Square from = pieces.PopLeastSignificantBit();
  Bitboard attacks =
    GenerateAttacks<Piece>(from, position.GetPieces()) & targets;
  // ...
}
```

## The Position Class

TODO!