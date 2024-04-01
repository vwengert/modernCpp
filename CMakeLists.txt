cmake_minimum_required(VERSION 3.18)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    # Support Unix Makefiles and Ninja
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project(modernCpp VERSION 0.0.1 LANGUAGES CXX)
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# setting Debug Build Type if no type is set.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")


file(GLOB Library_SOURCES "src/*.cpp")
file(GLOB Library_HEADER "include/*.h")

add_subdirectory(mainlib)

add_executable(${PROJECT_NAME}
    ${Library_SOURCES}
    ${Library_HEADER}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

SET(LINK_LIBRARY
    modernLibrary
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LINK_LIBRARY}
)

enable_testing()
add_subdirectory(Tests)

# first we can indicate the documentation build as an option and set it to OFF by default
option(BUILD_DOC "Build documentation" OFF)

if(BUILD_DOC)
# check if Doxygen is installed
  find_package(Doxygen)
  if (DOXYGEN_FOUND)
      # # set input and output files
      set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/modern)
      set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
      
      # request to configure the file
      configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
      message("Doxygen build started")

      # note the option ALL which allows to build the docs together with the application
      add_custom_target( doc_doxygen ALL
          COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Generating API documentation with Doxygen"
          VERBATIM )
  else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
  endif (DOXYGEN_FOUND)
endif(BUILD_DOC)
