# Chess Project

This repository contains a skeleton implementation of a functional-style C++ chess game. It uses Qt Quick for the user interface.

## Components

- **Start Page**: Handles user login and registration.
- **Game Setup Page**: Select between AI vs Player or Player vs Player, choose colors or random, and set time limits.
- **Game Page**: Implements the chess rules and board rendering.

## Building

1. Install Qt6 (Qt Quick, Widgets, Qml modules).
2. Configure the project with CMake. If CMake cannot find Qt automatically,
   specify the installation path via `CMAKE_PREFIX_PATH`:
   ```bash
   cmake -S . -B build \
     -DCMAKE_PREFIX_PATH="C:/Qt/6.8.3/mingw_64"
   cmake --build build
   ```
3. Run the executable `build/src/chess_program`.

If building on a headless machine, run the program with the `offscreen` Qt
platform plugin:
```bash
QT_QPA_PLATFORM=offscreen build/src/chess_program
```

The QML files are compiled into the binary via Qt's resource system. Ensure you rebuild after modifying any `.qml` files.
