include(FetchContent)

# Disable Google Benchmark's own tests
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.5
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(googlebenchmark)

add_executable(BigInt-Benchmarks
        benchmark_bigint.cpp
)

target_link_libraries(
        BigInt-Benchmarks
        PRIVATE
        BigInt
        benchmark::benchmark_main
)