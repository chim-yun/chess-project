cmake_minimum_required(VERSION 3.16)
project(ChessProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Locate the Qt6 development files. Ensure you are using Qt 6.4 or newer.
# If they are not found automatically, provide the path to your Qt installation
# via the CMAKE_PREFIX_PATH variable or the Qt6_DIR cache entry.
find_package(Qt6 6.0 REQUIRED COMPONENTS Core Gui Widgets Quick Qml)

qt_standard_project_setup()

add_subdirectory(src)
