# Generic ARM Cortex-M4 toolchain for STM32F401 (Black Pill)

# Target system
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

# Toolchain prefix
set(CROSS_COMPILE arm-none-eabi-)

# Compilers
set(CMAKE_C_COMPILER    ${CROSS_COMPILE}gcc)
set(CMAKE_CXX_COMPILER  ${CROSS_COMPILE}g++)
set(CMAKE_ASM_COMPILER  ${CMAKE_C_COMPILER})
set(CMAKE_LINKER        ${CROSS_COMPILE}g++)
set(CMAKE_OBJCOPY       ${CROSS_COMPILE}objcopy)
set(CMAKE_SIZE          ${CROSS_COMPILE}size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

# Bypass default linker
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# FPU mode selection.
# Allowed values: hard, softfp, soft
set(FPU_MODE "hard" CACHE STRING "Floating-point ABI mode for STM32F401")
set_property(CACHE FPU_MODE PROPERTY STRINGS hard softfp soft)

# Target CPU options
if(FPU_MODE STREQUAL "hard")
    set(TARGET_FPU_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
    set(TARGET_ASM_FPU_DEFS "-DREBEL_FPU_HARD=1")
elseif(FPU_MODE STREQUAL "softfp")
    set(TARGET_FPU_FLAGS "-mfloat-abi=softfp -mfpu=fpv4-sp-d16")
    set(TARGET_ASM_FPU_DEFS "-DREBEL_FPU_SOFTFP=1")
elseif(FPU_MODE STREQUAL "soft")
    set(TARGET_FPU_FLAGS "-mfloat-abi=soft")
    set(TARGET_ASM_FPU_DEFS "-DREBEL_FPU_SOFT=1")
else()
    message(FATAL_ERROR "Invalid FPU_MODE='${FPU_MODE}'. Use one of: hard, softfp, soft")
endif()

set(TARGET_CPU_FLAGS "-mcpu=cortex-m4 ${TARGET_FPU_FLAGS}")
set(TARGET_COMPILE_FLAGS "-ffunction-sections -fdata-sections")

# No standard libraries
set(CMAKE_C_FLAGS_INIT "${TARGET_CPU_FLAGS} ${TARGET_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -fno-rtti -fno-exceptions -fno-threadsafe-statics")
set(CMAKE_ASM_FLAGS_INIT "${TARGET_CPU_FLAGS} ${TARGET_ASM_FPU_DEFS} -x assembler-with-cpp -MMD -MP")

set(CMAKE_EXE_LINKER_FLAGS_INIT "${TARGET_CPU_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} --specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,-Map=${CMAKE_PROJECT_NAME}.map")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,--print-memory-usage")
