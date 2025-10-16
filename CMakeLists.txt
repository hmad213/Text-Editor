cmake_minimum_required(VERSION 3.16)
project(QtApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt 6 (Core, Gui, Widgets)
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Source, headers, and UI files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
)
set(HEADERS
    include/mainwindow.h
)
set(UI
    forms/mainwindow.ui
)

# Create executable
qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
