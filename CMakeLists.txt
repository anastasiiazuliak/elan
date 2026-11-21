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
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
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
if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows"
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-mingw-dynamic"
    )
    target_compile_definitions(ELAN PRIVATE _WIN32_WINNT=0x0601)
endif()

find_package(Crow CONFIG REQUIRED)
target_link_libraries(ELAN PRIVATE Crow::Crow)
target_compile_definitions(ELAN PRIVATE ELAN_PROJECT_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")

if(MSVC)
    target_compile_options(ELAN PRIVATE /utf-8)
endif()
