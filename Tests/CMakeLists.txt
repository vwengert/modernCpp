set(Test modernTests)
set(benchmark testBenchmark)

FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(benchmark REQUIRED)

set(TEST_PROJECT_SOURCES
        testMain.cpp
        testMore.cpp
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
        gtest::gtest
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
