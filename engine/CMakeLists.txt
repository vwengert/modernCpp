project(engine VERSION 0.0.1 LANGUAGES CXX)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

list(APPEND Library_SOURCES
        src/openGL.cpp
)

list(APPEND Library_HEADER
        include/openGL.h
)

FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)


add_library(${PROJECT_NAME} STATIC
        ${Library_SOURCES}
        ${Library_HEADER}
)

target_include_directories(${PROJECT_NAME} PUBLIC
        include
)

SET(LINK_LIBRARY
        glad
        glfw
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${LINK_LIBRARY}
)
