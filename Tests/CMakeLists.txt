set(Test modernTests)
set(benchmark testBenchmark)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

add_executable(${Test}
        testMain.cpp
        testMore.cpp
        testTemplateArchitecture.cpp
)

add_executable(${benchmark}
        benchmark.cpp
)

target_link_libraries(${Test}
        PUBLIC
        gtest::gtest
        modernLibrary::modernLibrary
        basicLibrary::basicLibrary
)

target_link_libraries(${benchmark}
        PUBLIC
        benchmark::benchmark
        modernLibrary::modernLibrary
        basicLibrary::basicLibrary
)

add_test(
        NAME ${Test}
        COMMAND ${Test}
)
