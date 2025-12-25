---
title: "Installation"
summary: "Technical requirements and build instructions for FollyChess."
date: 2025-12-25T11:32:00+02:00
lastmod: 2025-12-25T11:32:00+02:00
draft: false
weight: 10
toc: true
seo:
  title: "Build FollyChess from Source"
  description: "Step-by-step guide to compiling FollyChess using Bazel."
---

## Building from Source

Currently, FollyChess is distributed as source code. To run the engine, you will
need to build it for your specific environment.

### Prerequisites

Ensure your environment is set up with the following:

1. **C++23 Compiler:** Use [Clang 17+](https://llvm.org/) or a modern equivalent
   that supports the C++23 standard.
2. **Bazel:** The project uses
   the [Bazel build system](https://bazel.build/start). Ensure it is installed
   and available in your `PATH`.

### Compiling

To build the optimized **UCI (Universal Chess Interface)** command-line binary,
execute the following command in your terminal:

```shell
bazel build --compilation_mode=opt //cli:follychess
```

{{< callout note >}}
Using `--compilation_mode=opt` ensures the compiler applies performance-critical
optimizations.
{{< /callout >}}

Once the build is complete, the executable binary will be located at
`bazel-bin/cli/follychess`.
