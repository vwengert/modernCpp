cmake_minimum_required(VERSION 3.18)

#project(modernCpp VERSION 0.0.1 LANGUAGES CXX)
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

file(GLOB Library_SOURCES "src/*.cpp")
file(GLOB Library_HEADER "include/*.h")

add_subdirectory(mainlib)

add_executable(${PROJECT_NAME}
    ${Library_SOURCES}
    ${Library_HEADER}
)

SET(LINK_LIBRARY
    modernLibrary
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LINK_LIBRARY}
)

add_subdirectory(Tests)

enable_testing()

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}.exe)
set_tests_properties(${PROJECT_NAME}
    PROPERTIES PASS_REGULAR_EXPRESSION "^[0-9 ]+"
)
