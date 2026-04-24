cmake_minimum_required(VERSION 3.10)
project(ojbench_problem_097 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optimize for OJ
if (NOT CMAKE_CXX_FLAGS)
    set(CMAKE_CXX_FLAGS "-O2 -pipe -static -s")
endif()

add_executable(code src/main.cpp)
target_compile_options(code PRIVATE -Wall -Wextra -Wno-unused-parameter)

