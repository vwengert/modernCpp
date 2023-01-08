cmake_minimum_required(VERSION 3.25)

project(modernCpp VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

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
