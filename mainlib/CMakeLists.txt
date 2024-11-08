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
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME}
        PRIVATE
        cxx_std_20
)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        MODERN_LIBRARY_EXPORTS
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(EXPORT ${PROJECT_NAME}Config
        FILE ${PROJECT_NAME}Config.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION lib/cmake/${PROJECT_NAME}
)