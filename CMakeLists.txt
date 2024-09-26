cmake_minimum_required(VERSION 3.10)

project(QtOverlayWindow VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(overlay main.cpp)

target_link_libraries(overlay PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)

