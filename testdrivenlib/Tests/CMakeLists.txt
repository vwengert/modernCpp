set(Test testdrivenTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(access_private REQUIRED)

add_executable(${Test}
        testsoundex.cpp
        testretweetcollection.cpp
        testwithparameters.cpp
        testwithmock.cpp
)

target_link_libraries(${Test}
        PUBLIC
        gtest::gtest
        testdrivenLibrary::testdrivenLibrary
        access_private::access_private
)

add_test(
        NAME ${Test}
        COMMAND ${Test}
)
