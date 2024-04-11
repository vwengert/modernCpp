set(benchmark testBenchmark)

include(FetchContent)

set(PROJECT_SOURCES
        benchmark.cpp
)

add_executable(${benchmark}
        ${PROJECT_SOURCES}
)

target_link_libraries(${benchmark} PUBLIC
        modernLibrary
        benchmark::benchmark
)

FetchContent_Declare(GoogleBenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.3
)

FetchContent_MakeAvailable(GoogleBenchmark)
