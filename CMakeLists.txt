cmake_minimum_required(VERSION 3.16)
project(ChessProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.0 REQUIRED COMPONENTS Core Gui Widgets Quick Qml)

qt_standard_project_setup()

add_subdirectory(src)
