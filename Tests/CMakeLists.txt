set(Test modernTests)
set(benchmark testBenchmark)

FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(benchmark REQUIRED)

add_executable(${Test}
        testMain.cpp
        testMore.cpp
)

add_executable(${benchmark}
        benchmark.cpp
)

target_link_libraries(${Test}
        PUBLIC
        gtest::gtest
        modernLibrary
)
target_link_libraries(${benchmark}
        PUBLIC
        benchmark::benchmark
        modernLibrary
)

add_test(
        NAME ${Test}
        COMMAND ${Test}
)
