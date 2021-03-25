cmake_minimum_required(VERSION 3.14)
project(Homework)

# Using -Wall is required:
add_compile_options(-Wall)

# These compile flags are highly recommended, but not required:
add_compile_options(-Wextra -Wpedantic)
add_compile_options(-fstack-protector-all -g -O3 -std=c++17 -Walloc-zero)

# add_compile_options must be BEFORE add_executable or add_library.

add_library(hw4 Ratio.cc)
add_executable(test test.cc)
target_link_libraries(test hw4)
# Create a tar file every time:
add_custom_target(hw4.tar ALL COMMAND tar -cf hw4.tar Ratio.cc Ratio.h test.cc CMakeLists.txt)
