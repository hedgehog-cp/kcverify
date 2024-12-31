# kcverify

KanColle Verification Tool

Feature:

- Rigorous numerical calculations
- fast

## Development Environment

- WSL2
- Ubuntu 24.04
- VSCode

## Dependency

### Build Tool

- Compiler
  - GCC14.2
  - `sudo apt install gcc`
  - C++17 and part of C++20, C++23
- [CMake](https://cmake.org/)
  - `sudo apt install cmake`

### Library

- [Boost](https://www.boost.org/)
  - for Interval arithmetic, Validated Numerics
  - `sudo apt install -libboost-all-dev`
- [glaze](https://github.com/stephenberry/glaze)
  - for JSON
- [range-v3](https://github.com/ericniebler/range-v3)
  - for alternative to C++26 std::ranges::views::concat
  - `sudo apt install librange-v3-dev librange-v3-doc`

### Documentation

- doxygen
  - `sudo apt install doxygen`
- graphviz
  - `sudo apt install graphviz`

### Other

- clang-format
- clangd
