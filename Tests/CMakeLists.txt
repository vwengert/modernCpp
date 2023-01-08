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
    GIT_TAG release-1.12.1
    )

FetchContent_MakeAvailable(GoogleTest)
