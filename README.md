# kcverify

KanColle Verification Tool

Feature:

- Rigorous numerical calculations

## Development Environment

- WSL2
- Ubuntu 24.04
- VSCode

## Dependency

### Build Tool

- Compiler
  - GCC14.2 or clang19.1
  - C++17 and part of C++20, C++23
- [CMake](https://cmake.org/)

### Library

- [glaze](https://github.com/stephenberry/glaze)
- [range-v3](https://github.com/ericniebler/range-v3)
  - for alternative to C++26 std::ranges::views::concat

### Documentation

- doxygen
- graphviz

### Other

- clang-format
- clangd
