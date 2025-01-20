cmake_minimum_required(VERSION 3.10)

# Project Name and Version
project(B VERSION 1.0)

# Set C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories for header files
include_directories(include)

# Define executable 'b' from main.cpp and Node.cpp
add_executable(b src/main.cpp src/Node.cpp)

# Define executable 'blockchainSimulator' from Simulator.cpp and Node.cpp
add_executable(blockchainSimulator src/Simulator.cpp src/Node.cpp)

# Compiler flags (optional but recommended)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(b PRIVATE -Wall -Wextra -pedantic -O2)
    target_compile_options(blockchainSimulator PRIVATE -Wall -Wextra -pedantic -O2)
elseif (MSVC)
    target_compile_options(b PRIVATE /W4 /O2)
    target_compile_options(blockchainSimulator PRIVATE /W4 /O2)
endif()

# Find and link the pthread library for multithreading support
find_package(Threads REQUIRED)
target_link_libraries(b PRIVATE Threads::Threads)
target_link_libraries(blockchainSimulator PRIVATE Threads::Threads)
