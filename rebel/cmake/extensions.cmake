# --------------------------------------
# Installs dependency by downloading it
#
# ADDRESS git repository url
# NAME directory name which dependency gets cloned to
# VERSION dependency version: branch or tag
#
# RES_INSTALL_DIR variable to store installation dir to
# --------------------------------------
function(pat_install_dep)
    set(options OPTIONAL)
    set(oneValueArgs ADDRESS NAME VERSION RES_INSTALL_DIR)
    set(multiValueArgs "")
    cmake_parse_arguments(PARSE_ARGV 0 ARG "${options}" "${oneValueArgs}" "${multiValueArgs}")

    set(CLONE_DIR "${CMAKE_SOURCE_DIR}/vendor/${ARG_NAME}")

    # Only download if directory doesn't exist.
    if (NOT EXISTS "${CLONE_DIR}")
        message(STATUS "Downloading ${ARG_NAME}...")
        execute_process(
                COMMAND git clone --depth 1 --branch ${ARG_VERSION} --recurse-submodules "${ARG_ADDRESS}" "${CLONE_DIR}"
                RESULT_VARIABLE GIT_RESULT
        )
        if (NOT GIT_RESULT EQUAL "0")
            if (ARG_OPTIONAL)
                message(STATUS "Failed to clone ${ARG_NAME}")
            else ()
                message(FATAL_ERROR "Failed to clone ${ARG_NAME}")
            endif ()
        endif ()
    endif ()

    set(${ARG_RES_INSTALL_DIR} ${CLONE_DIR})
    return(PROPAGATE ${ARG_RES_INSTALL_DIR})
endfunction()