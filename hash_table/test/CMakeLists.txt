cmake_minimum_required(VERSION 3.5.1)

enable_testing()

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(benchmark REQUIRED)

# create benchmarks
file(GLOB_RECURSE ALL_BENCHMARK_CPPS *benchmark.cpp)
file(GLOB_RECURSE ALL_TEST_CPPS *test.cpp)

foreach(ONE_BENCHMARK_CPP ${ALL_BENCHMARK_CPPS})
    get_filename_component(ONE_BENCH_EXEC ${ONE_BENCHMARK_CPP} NAME_WE)

    # Avoid name collision 
    set(BENCH_NAME ${PROJECT_NAME}_${ONE_BENCH_EXEC})

    # create benchmark
    add_executable(${BENCH_NAME} ${ONE_BENCHMARK_CPP})
    target_link_libraries(${BENCH_NAME} ${CMAKE_THREAD_LIBS_INIT} benchmark)
    target_compile_options(${BENCH_NAME} PUBLIC -std=c++17)
endforeach()

foreach(ONE_TEST_CPP ${ALL_TEST_CPPS})
    get_filename_component(ONE_TEST_EXEC ${ONE_TEST_CPP} NAME_WE)

    # Avoid name collision 
    set(TEST_NAME ${PROJECT_NAME}_${ONE_TEST_EXEC})

    # create test
    add_executable(${TEST_NAME} ${ONE_TEST_CPP})
    target_link_libraries(${TEST_NAME} ${CMAKE_THREAD_LIBS_INIT} gtest gtest_main)
    target_compile_options(${TEST_NAME} PUBLIC -std=c++17)
    add_test(${TEST_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME})
endforeach()
