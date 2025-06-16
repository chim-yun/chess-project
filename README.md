# Chess Project

This repository contains a skeleton implementation of a functional-style C++ chess game. It uses Qt Quick for the user interface.

## Components

- **Start Page**: Handles user login and registration.
- **Game Setup Page**: Select between AI vs Player or Player vs Player, choose colors or random, and set time limits.
- **Game Page**: Implements the chess rules and board rendering.

## Building

1. Install Qt6 (Qt Quick, Widgets, Qml modules).
2. Configure the project with CMake:
   ```bash
   cmake -S . -B build
   cmake --build build
   ```
3. Run the executable `build/src/chess_program`.

The QML files are compiled into the binary via Qt's resource system. Ensure you rebuild after modifying any `.qml` files.
