project(modernLibrary VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

list(APPEND Library_SOURCES
        src/factory.cpp
        src/mathematics.cpp
        src/modernLibrary.cpp
        src/singleton.cpp
        src/visitor.cpp
)

list(APPEND Library_HEADER
        include/abstractfabric.h
        include/decorator.h
        include/factory.h
        include/mathematics.h
        include/modernLibrary.h
        include/singleton.h
        include/visitor.h
)

add_library(${PROJECT_NAME} STATIC
        ${Library_SOURCES}
        ${Library_HEADER}
)

target_include_directories(${PROJECT_NAME} PUBLIC
        include
)
