project(
        modernLibrary
        VERSION 0.0.1
        LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED
        src/appconfigurator.cpp
        src/bridge.cpp
        src/configure.cpp
        src/factory.cpp
        src/ianimal.cpp
        src/ifood.cpp
        src/mathematics.cpp
        src/modernLibrary.cpp
        src/singleton.cpp
        src/visitor.cpp
)

target_compile_features(${PROJECT_NAME}
        PRIVATE
        cxx_std_20
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        MODERN_LIBRARY_EXPORTS)
