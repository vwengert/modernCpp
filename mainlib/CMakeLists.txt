project(modernLibrary VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

file(GLOB Library_SOURCES "src/*.cpp")
file(GLOB Library_HEADER "include/*.h")

add_library(test_${PROJECT_NAME}
    ${Library_SOURCES}
    ${Library_HEADER}
)

add_library(${PROJECT_NAME}
    ${Library_SOURCES}
    ${Library_HEADER}
)

target_compile_options(${PROJECT_NAME} PUBLIC 
    "$<$<CONFIG:Debug>:-fsanitize=address>"
)

target_link_options(${PROJECT_NAME} PUBLIC     
    "$<$<CONFIG:Debug>:-fsanitize=address>"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)

target_include_directories(test_${PROJECT_NAME} PUBLIC
    include
)