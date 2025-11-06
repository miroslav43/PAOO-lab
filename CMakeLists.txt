cmake_minimum_required(VERSION 3.10)

# Project name and version
project(StartupAccelerator VERSION 1.0 LANGUAGES CXX)

# Set C++ standard (C++14 for move semantics)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/Project.cpp
    src/Mentor.cpp
    src/Startup.cpp
    src/Accelerator.cpp
    src/Logger.cpp
)

# Header files (for IDE support)
set(HEADERS
    include/Project.hpp
    include/Mentor.hpp
    include/Startup.hpp
    include/Accelerator.hpp
    include/Logger.hpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Print configuration information
message(STATUS "========================================")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source Directory: ${PROJECT_SOURCE_DIR}")
message(STATUS "Binary Directory: ${CMAKE_BINARY_DIR}")
message(STATUS "========================================")

