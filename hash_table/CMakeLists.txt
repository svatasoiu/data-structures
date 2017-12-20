cmake_minimum_required(VERSION 3.5.1)

project(hash_table)

include_directories(${PROJECT_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
