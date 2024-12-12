project(
        basicLibrary
        VERSION 0.0.1
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif ()

add_library(${PROJECT_NAME} SHARED
        src/basicLibrary.cpp
        include/node.h
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION}
)

target_compile_options(${PROJECT_NAME}
        PRIVATE
        -fvisibility=hidden
        -fvisibility-inlines-hidden
)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        BASIC_LIBRARY_EXPORTS
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ${PROJECT_NAME}Config
        FILE ${PROJECT_NAME}Config.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION lib/cmake/${PROJECT_NAME}
)
