# C++ Custom JSON Parser

A lightweight, dependency-free JSON parser written in standard C++17. This project was built to explore lexical analysis, recursive descent parsing, and the advanced use of C++ Standard Template Library (STL) containers like `std::variant`.

## Features
- **Zero Dependencies:** Uses only the C++ standard library.
- **Full JSON Spec Support:** Handles Objects, Arrays, Strings, Numbers, Booleans, and Nulls.
- **In-Memory AST:** Converts raw text into an easily queryable C++ tree structure.

## Technical Stack
- **Language:** C++17
- **Build System:** CMake (or standard g++/clang++ compiler)
- **Key Concepts:** Lexing/Tokenization, Recursion, `std::variant`, `std::map`, `std::vector`.

## Project Structure
```text
cpp-json-parser/
├── src/
│   ├── main.cpp         # Entry point and testing
│   ├── lexer.cpp        # Tokenization logic
│   ├── lexer.h
│   ├── parser.cpp       # Tree building logic
│   ├── parser.h
│   ├── json_value.cpp   # Data structure definitions
│   └── json_value.h
├── data/
│   └── test.json        # Sample JSON file for testing
├── CMakeLists.txt       # Build configuration
└── README.md