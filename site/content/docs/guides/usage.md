---
title: "Usage"
summary: "How to run FollyChess and connect it to your favorite chess interface."
date: 2023-09-07T16:05:00+02:00
lastmod: 2025-12-25T11:32:00+02:00
draft: false
weight: 20
toc: true
seo:
  title: "Using FollyChess with GUIs and CLI"
  description: "Learn how to use FollyChess via the command line or by connecting it to a UCI-compatible GUI."
---

Once you have [compiled the engine](/docs/guides/installation), you can use it
either
through a Graphical User Interface (GUI) or directly via the Command Line
Interface (CLI).

## Using with a Chess GUI

FollyChess is
a [UCI-compatible engine](https://en.wikipedia.org/wiki/Universal_Chess_Interface),
meaning it does
not have its own
graphics. Instead, it "plugs into" a chess interface. We recommend using one of
these GUIs:

* [Arena](http://www.playwitharena.de/)
* [BanksiaGUI](https://banksiagui.com/)
* [Cutechess](https://github.com/cutechess/cutechess)
* [HIARCS Chess Explorer](https://www.hiarcs.com/chess-explorer.html)

In your GUI of choice, add a new engine and select the
`bazel-bin/cli/follychess` binary when prompted.

## Running via CLI

You can interact with the engine directly via standard input for debugging or
scripting.

```shell
bazel-bin/cli/follychess
```

Once running, the engine waits for commands from standard input. FollyChess
currently supports a subset of the UCI protocol. Supported commands are covered
below.

### `uci`

Initializes the UCI protocol. The engine will identify itself and list its
available options.

### `isready`

Used to synchronize with the engine. FollyChess will respond with `readyok` once
it has finished internal setup and is ready to receive move or search commands.

### `d`

**Custom Command.** Displays a representation of the current position.

Example:

```text
d
8: r n b q k b n r
7: p p p p p p p p
6: . . . . . . . .
5: . . . . . . . .
4: . . . . . . . .
3: . . . . . . . .
2: P P P P P P P P
1: R N B Q K B N R
   a b c d e f g h

   w KQkq - 0 1
```

### `position`

This command tells the engine what the board looks like. It supports these
formats:

* **Starting Position**: `position startpos` sets the board to the starting
  position:

  ```text
    position startpos
    d
    8: r n b q k b n r
    7: p p p p p p p p
    6: . . . . . . . .
    5: . . . . . . . .
    4: . . . . . . . .
    3: . . . . . . . .
    2: P P P P P P P P
    1: R N B Q K B N R
    a b c d e f g h
    
    w KQkq - 0 1
  ```

* **FEN String:** `position fen <fenstring>` sets the board to a specific state
  using [Forsyth-Edwards Notation](https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation):

  ```text
    position fen 8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1
    d
    8: . . . . . . . .
    7: . . p . . . . .
    6: . . . p . . . .
    5: K P . . . . . r
    4: . R . . . p . k
    3: . . . . . . . .
    2: . . . . P . P .
    1: . . . . . . . .
    a b c d e f g h
    
    w - - 0 1
    ```

* **Adding Moves:**
  `position [startpos | fen <fenstring>] moves <move1> <move2> ...` applies a
  sequence of moves to the specified position:

  ```text
  position startpos moves e2e4 e7e5 g1f3
  d
  8: r n b q k b n r
  7: p p p p . p p p
  6: . . . . . . . .
  5: . . . . p . . .
  4: . . . . P . . .
  3: . . . . . N . .
  2: P P P P . P P P
  1: R N B Q K B . R
  a b c d e f g h
  
  b KQkq - 3 2
  ```

Moves
use [long algebraic notation](https://www.chessprogramming.org/Algebraic_Chess_Notation):

| Type          | Format              | Example                                           |
|:--------------|:--------------------|:--------------------------------------------------|
| **Standard**  | `<from><to>`        | `e2e4`, `g1f3`                                    |
| **Castling**  | `<from><to>`        | `e1g1` (white kingside), `e8c8` (black queenside) |
| **Promotion** | `<from><to><piece>` | `a7a8q` (queen), `h2h1n` (knight)                 |

### `go`

Calculates the best move with a user-specified depth:

```text
go depth 3
info depth 3 seldepth 3 nodes 1024 nps 175402 tbhits 36
info depth 3 seldepth 4 nodes 2048 nps 241766 tbhits 133
info depth 3 seldepth 3 nodes 3072 nps 286567 tbhits 166
info depth 3 seldepth 3 nodes 4096 nps 286033 tbhits 187
info depth 3 seldepth 3 nodes 5120 nps 310058 tbhits 264
bestmove b1c3
```

### `quit`

Terminates the engine process.