if (GIT_EXECUTABLE)
    get_filename_component(SRC_DIR ${SRC} DIRECTORY)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --match "v*"
            WORKING_DIRECTORY ${SRC_DIR}
            OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
            RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (NOT GIT_DESCRIBE_ERROR_CODE)
        set(MODERNCPP_VERSION ${GIT_DESCRIBE_VERSION})
    endif ()
endif ()

if (NOT DEFINED MODERNCPP_VERSION)
    set(MODERNCPP_VERSION v0.0.0-unknown)
    message(WARNING "Failed to determine VERSION from Git tags. Using default version \"${MODERNCPP_VERSION}\".")
endif ()

configure_file(${SRC} ${DST} @ONLY)