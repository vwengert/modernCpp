set(Test modernTests)
set(Benchmark testBenchmark)
set(UTest uTest)

include(FetchContent)
FetchContent_Declare(
        cpputest
        GIT_REPOSITORY https://github.com/cpputest/cpputest.git
        GIT_TAG master
)

FetchContent_MakeAvailable(CppUTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

add_executable(${Test}
        testMain.cpp
        testMore.cpp
        testTemplateArchitecture.cpp
)

add_executable(${UTest}
        cpputestmain.cpp
)

add_executable(${Benchmark}
        benchmark.cpp
)

target_link_libraries(${Test}
        PUBLIC
        gtest::gtest
        modernLibrary::modernLibrary
        basicLibrary::basicLibrary
)

target_link_libraries(${UTest}
        PUBLIC
        CppUTest::CppUTest
        modernLibrary::modernLibrary
        basicLibrary::basicLibrary
)

target_link_libraries(${Benchmark}
        PUBLIC
        benchmark::benchmark
        modernLibrary::modernLibrary
        basicLibrary::basicLibrary
)

add_test(
        NAME ${Test}
        COMMAND ${Test}
)

include(CppUTest)
cpputest_discover_tests(${UTest})
