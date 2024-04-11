set(Test modernTests)

include(FetchContent)

set(PROJECT_SOURCES
        testMain.cpp
)

add_executable(${Test}
        ${PROJECT_SOURCES}
)

target_link_libraries(${Test} PUBLIC
        gtest_main
        gmock_main
        modernLibrary
)

add_test(
        NAME ${Test}
        COMMAND ${Test}
)

FetchContent_Declare(GoogleTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(GoogleTest)
