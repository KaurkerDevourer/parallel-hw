cmake_minimum_required(VERSION 3.24)
project(hw1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(parlaylib
    URL https://codeload.github.com/cmuparlay/parlaylib/tar.gz/51017699dcc421f80479cdb238d3092233ad0d26
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    TIMEOUT 30
)
FetchContent_MakeAvailable(parlaylib)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE GTest::gtest_main parlay)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_Declare(googlebenchmark
    URL https://codeload.github.com/google/benchmark/tar.gz/refs/tags/v1.10.0
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    TIMEOUT 30
)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE benchmark::benchmark parlay)
