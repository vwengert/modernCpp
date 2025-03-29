set(Test testdrivenTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${Test}
        testsoundex.cpp
        testretweetcollection.cpp
        testwithparameters.cpp
        testwithmock.cpp
        testgeoserver.cpp
        testsupermarketpricing.cpp
)

target_link_libraries(${Test}
        PUBLIC
        gmock
        gmock_main
        testdrivenLibrary::testdrivenLibrary
)

add_test(
        NAME ${Test}
        COMMAND ${Test}
)
