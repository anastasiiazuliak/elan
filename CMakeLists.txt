# ============================================
# ELAN Project Configuration
# ============================================

# Minimum required CMake version
cmake_minimum_required(VERSION 3.16)

# Project name
project(ELAN)

# Use modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================
# Include Directories
# ============================================
# Add paths where header files are located.
# This allows using clean includes like:
#   #include "elan/domain/Client.h"
include_directories(
    core/include
    core/src
)

# ============================================
# Source Files
# ============================================
# Automatically collect all .cpp files from project directories.
# This eliminates the need to manually update the list
# when new files are added.
file(GLOB_RECURSE SOURCES
    app/*.cpp
    core/src/api/*.cpp
    core/src/common/*.cpp
    core/src/domain/*.cpp
    core/src/dtos/*.cpp
    core/src/services/*.cpp
    core/src/storage/*.cpp
)

# ============================================
# Executable Target
# ============================================
# Create the final executable from collected source files.
add_executable(ELAN ${SOURCES})

# ============================================
# Link Libraries
# ============================================
target_include_directories(ELAN PRIVATE
    ${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-mingw-dynamic/include
)

# ============================================
# Notes
# ============================================
# - Build commands:
#     mkdir build
#     cd build
#     cmake ..
#     cmake --build .
#
# - This setup is platform-independent and works on:
#     Windows / Linux / macOS
#
# - Designed for scalability and clean project structure
# ===========================================

#Compiler definition
add_compile_definitions(_WIN32_WINNT=0x0601)