set(Test testdrivenTests)

find_package(GTest REQUIRED)

add_executable(${Test}
        testsoundex.cpp
)

target_link_libraries(${Test}
        PUBLIC
        gtest::gtest
)

add_test(
        NAME ${Test}
        COMMAND ${Test}
)
