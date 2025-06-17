# Build configuration for chess_program

# List of C++ source files
set(PROJECT_SOURCES
    GameAdapter.cpp
    GameLogic.cpp
    GameWindow.cpp
    StockfishAI.cpp
    main.cpp
)

# Create the executable
qt_add_executable(chess_program
    ${PROJECT_SOURCES}
)

# Bundle QML resources so the UI loads from the binary
qt_add_resources(chess_program qml_resources
    PREFIX "/"
    FILES
        ${CMAKE_SOURCE_DIR}/qml/ChessGame.qml
        ${CMAKE_SOURCE_DIR}/qt/Game_board.ui.qml
        ${CMAKE_SOURCE_DIR}/qt/Screen01.ui.qml
)

# Link against Qt libraries
target_link_libraries(chess_program
    PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Quick Qt6::Qml
)
