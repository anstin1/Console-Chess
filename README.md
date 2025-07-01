# Console Chess

A C++ console-based chess game that allows two players to play chess in the terminal. The project is structured for clarity and extensibility, making it easy for developers to understand, maintain, and extend.

## Table of Contents
- [Features](#features)
- [Project Structure](#project-structure)
- [Build Instructions](#build-instructions)
- [How to Play](#how-to-play)
- [Code Overview](#code-overview)
- [Extending the Codebase](#extending-the-codebase)

---

## Features
- Full chess rules: movement, castling, en passant, pawn promotion, and check detection.
- Console-based board rendering and move input.
- Simple, object-oriented design for easy extension.

## Project Structure
```
console_chess/
├── include/           # Header files (class declarations)
│   ├── Piece.h        # Abstract base class for all pieces
│   ├── Pawn.h         # Pawn class
│   ├── Rook.h         # Rook class
│   ├── Knight.h       # Knight class
│   ├── Bishop.h       # Bishop class
│   ├── King.h         # King class
│   ├── Queen.h        # Queen class
│   ├── Game.h         # Game logic and board state
│   └── MainLoop.h     # Main game loop
├── src/               # Source files (implementations)
│   ├── Piece.cpp      # Piece base class implementation
│   ├── Pawn.cpp       # Pawn logic
│   ├── Rook.cpp       # Rook logic
│   ├── Knight.cpp     # Knight logic
│   ├── Bishop.cpp     # Bishop logic
│   ├── King.cpp       # King logic
│   ├── Queen.cpp      # Queen logic
│   ├── Game.cpp       # Game logic implementation
│   ├── MainLoop.cpp   # Main loop implementation
│   └── Main.cpp       # Application entry point
├── CMakeLists.txt     # CMake build configuration
├── Chess.sln          # Visual Studio solution file
```

## Build Instructions

### Using CMake (Recommended)
1. Ensure you have CMake (>=3.10) and a C++17-compatible compiler installed.
2. In the project root, run these commands:
   ```bash
   # Configure the project (generates build files)
   cmake -S . -B build
   
   # Build the project in Release configuration
   cmake --build build --config Release
   ```
3. The executable `ConsoleChess.exe` will be created in the `build/Release` directory.

**Alternative one-liner:**
```bash
cmake -S . -B build && cmake --build build --config Release
```

### Using Visual Studio
- Open `Chess.sln` in Visual Studio 2017 or later and build the solution.

## How to Play
- Run the executable from a terminal:
  ```sh
  ./ConsoleChess
  ```
- The board will be displayed in the console.
- Enter moves in algebraic notation (e.g., `e2e4` to move a piece from e2 to e4).
- Type `exit` or `quit` to end the game.
- The game enforces chess rules, including castling, en passant, and pawn promotion.

## Code Overview

### Main Components
- **MainLoop**: Handles the main game loop, user input, and game progression.
- **Game**: Manages the board state, turn logic, move validation, and game rules.
- **Piece (Abstract Base Class)**: Defines the interface for all chess pieces, including move calculation and rendering.
- **Pawn, Rook, Knight, Bishop, King, Queen**: Implement specific movement and rules for each piece type.

### Class Relationships
- All pieces inherit from `Piece` and implement their own `calcPossibleMoves` method.
- The `Game` class holds an 8x8 board of `Piece*` and manages all game logic.
- `MainLoop` creates a `Game` instance and interacts with the user.

### Move Validation
- Each piece calculates its possible moves based on the current board state.
- The `Game` class checks if a move is valid, handles special moves (castling, en passant, promotion), and updates the board.
- The game checks for check and checkmate conditions after each move.

## Extending the Codebase
- To add new features (e.g., AI, move history, GUI):
  - Extend the `Game` or `MainLoop` classes as needed.
  - Add new piece types by inheriting from `Piece` and implementing movement logic.
  - Refactor or add methods for new rules or UI features.
- The code is modular and object-oriented, making it straightforward to maintain and extend.

## License
This project is provided as-is for educational purposes. 