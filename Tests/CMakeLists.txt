set(Test modernTests)
set(benchmark testBenchmark)

include(FetchContent)

set(TEST_PROJECT_SOURCES
        testMain.cpp
)
set(BENCH_PROJECT_SOURCES
        benchmark.cpp
)

add_executable(${Test}
        ${TEST_PROJECT_SOURCES}
)
add_executable(${benchmark}
        ${BENCH_PROJECT_SOURCES}
)

target_link_libraries(${Test} PUBLIC
        gtest_main
        gmock_main
        modernLibrary
)
target_link_libraries(${benchmark} PUBLIC
        modernLibrary
        benchmark::benchmark
)

add_test(
        NAME ${Test}
        COMMAND ${Test}
)

FetchContent_Declare(GoogleTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
FetchContent_Declare(GoogleBenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.3
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(GoogleTest)
FetchContent_MakeAvailable(GoogleBenchmark)
