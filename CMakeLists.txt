cmake_minimum_required(VERSION 3.28.3)
project(BigInt)

# Enforce C++20 and disable compiler-specific extensions
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

include(CTest)
add_subdirectory(tests)

# Benchmarks are disabled by default
option(BIGINT_BUILD_BENCHMARKS "Build BigInt benchmarks" ON)

if(BIGINT_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()