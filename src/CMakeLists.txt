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
# QML resources packaged with the executable
set(QML_FILES
    ../qml/ChessGame.qml
    ../qt/Game_board.ui.qml
    ../qt/Screen01.ui.qml
)

# Make sure the resource names are relative so the files are accessible via
# qrc:/qml/... and qrc:/qt/...
set_source_files_properties(
    ../qml/ChessGame.qml PROPERTIES QT_RESOURCE_ALIAS qml/ChessGame.qml
)
set_source_files_properties(
    ../qt/Game_board.ui.qml PROPERTIES QT_RESOURCE_ALIAS qt/Game_board.ui.qml
)
set_source_files_properties(
    ../qt/Screen01.ui.qml PROPERTIES QT_RESOURCE_ALIAS qt/Screen01.ui.qml
)

qt_add_resources(chess_program qml_resources
    PREFIX "/"
    FILES
        ${QML_FILES}
)

# Link against Qt libraries
target_link_libraries(chess_program
    PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Quick Qt6::Qml
)
