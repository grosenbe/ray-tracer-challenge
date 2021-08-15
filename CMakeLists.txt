cmake_minimum_required (VERSION 3.20.0)
add_compile_options(-Wall -Wextra -Wpedantic -Werror -fstandalone-debug -pthread)
set(CMAKE_CXX_STANDARD 14)

project(ray-tracer-challenge)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)
