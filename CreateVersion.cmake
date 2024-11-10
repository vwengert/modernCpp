find_package(Git)
execute_process(
        COMMAND ${CMAKE_COMMAND}
        -D SRC=${CMAKE_SOURCE_DIR}/moderncpp_version.h.in
        -D DST=${CMAKE_BINARY_DIR}/moderncpp_version.h
        -D GIT_EXECUTABLE=${GIT_EXECUTABLE}
        -P ${CMAKE_SOURCE_DIR}/GenerateVersionHeader.cmake
)
include_directories(${CMAKE_BINARY_DIR})

file(READ "${CMAKE_BINARY_DIR}/moderncpp_version.h" VERSION_CONTENTS)
string(REGEX MATCH "#define MODERNCPP_VERSION \"([^\"]+)\"" VERSION_MATCHES ${VERSION_CONTENTS})
if (VERSION_MATCHES)
    set(MODERNCPP_VERSION ${CMAKE_MATCH_1})
endif ()

if (DEFINED MODERNCPP_VERSION)
    string(REGEX MATCH "v([0-9]+)\\.([0-9]+)\\.([0-9]+)" VERSION_MATCHES ${MODERNCPP_VERSION})
    if (VERSION_MATCHES)
        set(PROJECT_VERSION_MAJOR ${CMAKE_MATCH_1})
        set(PROJECT_VERSION_MINOR ${CMAKE_MATCH_2})
        set(PROJECT_VERSION_PATCH ${CMAKE_MATCH_3})
    else ()
        set(PROJECT_VERSION_MAJOR 0)
        set(PROJECT_VERSION_MINOR 0)
        set(PROJECT_VERSION_PATCH 0)
    endif ()
else ()
    set(PROJECT_VERSION_MAJOR 0)
    set(PROJECT_VERSION_MINOR 0)
    set(PROJECT_VERSION_PATCH 0)
endif ()