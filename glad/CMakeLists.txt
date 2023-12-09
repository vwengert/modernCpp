project(glad)

add_library(${PROJECT_NAME}
        glad.c
        include/glad/glad.h
        include/glad/khrplatform.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
)
