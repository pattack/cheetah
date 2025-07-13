cmake_minimum_required(VERSION 3.16)

# ========== Board and toolchain setup ==========
# You may include a separate toolchain file or set here:
set(BOARD habilis CACHE STRING "Target board")
if(NOT DEFINED BOARD)
    message(FATAL_ERROR "BOARD not defined. Please specify with -DBOARD=boardname")
endif()

# Include board toolchain
set(BOARD_DIR ${CMAKE_SOURCE_DIR}/boards/${BOARD})
set(CMAKE_TOOLCHAIN_FILE ${BOARD_DIR}/toolchain.cmake)

# Print selected board for clarity
message(STATUS "Building for board: ${BOARD}")
message(STATUS "Toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(rebel C CXX ASM)

# ========== Directories ==========
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(BOARDS_ROOT "${CMAKE_SOURCE_DIR}/boards")

# ========== Sources ==========
# Startup and linker script
set(STARTUP_SRC ${BOARD_DIR}/startup.s)
set(LINKER_SCRIPT ${BOARD_DIR}/linker.ld)

# Source files
set(SRC
        ${STARTUP_SRC}
        ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# ========== Compiler and linker flags ==========
# Shared C flags (warnings, optimization)
add_compile_options(-Wall -Wextra -Os)

# ========== Build main executable ==========
add_executable(firmware.elf ${SRC})

# Libraries
add_subdirectory(lib/board)
add_subdirectory(${BOARD_DIR}/lib/board)
add_subdirectory(lib/car)

# Linker script
set_target_properties(firmware.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
target_link_libraries(firmware.elf PRIVATE car board_${BOARD})
target_link_options(firmware.elf PRIVATE "-T${LINKER_SCRIPT}")

# ========== Generate HEX ==========
add_custom_command(TARGET firmware.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex firmware.elf firmware.hex
        COMMENT "Generating firmware.hex from firmware.elf"
)

# ========== Generate emulation.resc ==========
configure_file(
        ${BOARDS_ROOT}/emulation.resc.tpl
        ${CMAKE_BINARY_DIR}/emulation.resc
)

# ========== Clean target ==========
# Not needed: use `cmake --build . --target clean`

# ========== Print size ==========
add_custom_command(TARGET firmware.elf POST_BUILD
        COMMAND ${CMAKE_SIZE} firmware.elf
        COMMENT "Firmware size"
)

# Add custom target to run Renode test
add_custom_target(run_emulation
        COMMAND renode ${CMAKE_BINARY_DIR}/emulation.resc
        DEPENDS firmware.elf
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running Renode simulation for ${BOARD}"
)