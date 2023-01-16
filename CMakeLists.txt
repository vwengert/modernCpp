cmake_minimum_required(VERSION 3.20)

project(modernCpp VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

IF(!WIN)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fsanitize=address")
ENDIF()

set(PROJECT_SOURCES
    main.cpp
    )

add_subdirectory(mainlib)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    modernLibrary
    )

add_subdirectory(Tests)

enable_testing()
