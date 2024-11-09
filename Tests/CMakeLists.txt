set(Test modernTests)
set(benchmark testBenchmark)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)
#find_package(modernLibrary REQUIRED 0)

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
        modernLibrary::modernLibrary
)
target_link_libraries(${benchmark}
        PUBLIC
        benchmark::benchmark
        modernLibrary::modernLibrary
)

add_test(
        NAME ${Test}
        COMMAND ${Test}
)
