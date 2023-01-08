project(modernLibrary VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

set(Library_SOURCES
    src/modernLibrary.cpp
    src/fileHandling.cpp
    )

add_library(${PROJECT_NAME}
    ${Library_SOURCES}
    )

set_target_properties(${PROJECT_NAME} PROPERTIES 
    VERSION ${PROJECT_VERSION}
    )

target_include_directories(${PROJECT_NAME} PUBLIC 
    include
    )
