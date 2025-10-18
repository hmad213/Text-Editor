cmake_minimum_required(VERSION 3.16)
project(QtApp LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt6 modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Automatically collect source, header, and UI files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE UI_FILES "forms/*.ui")

# Create Qt executable
qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
)

# Include header directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
