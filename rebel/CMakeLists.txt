cmake_minimum_required(VERSION 3.16)

set(APPS_ROOT "${CMAKE_SOURCE_DIR}/apps")
set(CARS_ROOT "${CMAKE_SOURCE_DIR}/cars")

# ========== App setup ==========
set(APP starter CACHE STRING "Application logic target")
if(NOT DEFINED APP)
    message(FATAL_ERROR "APP not defined. Please specify with -DAPP=appname")
endif()

# Include app
set(APP_DIR ${APPS_ROOT}/${APP})

# ========== Car and toolchain setup ==========
# You may include a separate toolchain file or set here:
set(CAR habilis CACHE STRING "Target car which determines a combination of hardware and mechanical features")
if(NOT DEFINED CAR)
    message(FATAL_ERROR "CAR not defined. Please specify with -DCAR=carname")
endif()

# Include car toolchain
set(CAR_DIR ${CARS_ROOT}/${CAR})
set(CMAKE_TOOLCHAIN_FILE ${CAR_DIR}/toolchain.cmake)

# Print selected car and app for clarity
message(STATUS "Building app: ${APP} for car: ${CAR}")
message(STATUS "Toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(rebel C CXX ASM)

# ========== Directories ==========
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# ========== Sources ==========
# Startup and linker script
set(STARTUP_SRC ${CAR_DIR}/startup.s)
set(LINKER_SCRIPT ${CAR_DIR}/linker.ld)

# Source files
set(SRC
        ${STARTUP_SRC}
        ${SRC_DIR}/main.cpp
)

# ========== Compiler and linker flags ==========
# Shared C flags (warnings, optimization)
add_compile_options(-Wall -Wextra -Os)

# ========== Build main executable ==========
add_executable(firmware.elf ${SRC})

# Libraries
add_subdirectory(lib/toolkit)
add_subdirectory(lib/car)
add_subdirectory(${CAR_DIR}/lib/${CAR})
add_subdirectory(lib/app)
add_subdirectory(${APP_DIR}/lib/app)

# Linker script
set_target_properties(firmware.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
target_link_libraries(firmware.elf PRIVATE toolkit app_${APP} car_${CAR})
target_link_options(firmware.elf PRIVATE "-T${LINKER_SCRIPT}")

# ========== Generate HEX ==========
add_custom_command(TARGET firmware.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex firmware.elf firmware.hex
        COMMENT "Generating firmware.hex from firmware.elf"
)

# ========== Generate emulation.resc ==========
configure_file(
        ${CARS_ROOT}/emulation.resc.tpl
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
        COMMENT "Running Renode simulation for ${CAR}"
)