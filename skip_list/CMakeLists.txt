cmake_minimum_required(VERSION 3.5.1)

project(skip_list)

include_directories(${PROJECT_SOURCE_DIR}/include)

# set(LIB_NAME Lib_skiplist)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
