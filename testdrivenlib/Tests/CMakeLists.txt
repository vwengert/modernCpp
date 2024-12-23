set(Test testdrivenTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(${Test}
        testsoundex.cpp
        testretweetcollection.cpp
)

target_link_libraries(${Test}
        PUBLIC
        gtest::gtest
        testdrivenLibrary::testdrivenLibrary
)

add_test(
        NAME ${Test}
        COMMAND ${Test}
)
