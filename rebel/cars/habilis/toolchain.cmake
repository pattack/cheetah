# Generic ARM Cortex-M4 toolchain for STM32F401 (Black Pill)

# Target system
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Toolchain prefix
set(CROSS_COMPILE arm-none-eabi-)

# Compilers
set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++)
set(CMAKE_ASM_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_OBJCOPY ${CROSS_COMPILE}objcopy)
set(CMAKE_SIZE ${CROSS_COMPILE}size)

# Bypass default linker
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Target CPU options
set(TARGET_CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")

# No standard libraries
set(CMAKE_C_FLAGS_INIT "${TARGET_CPU_FLAGS} -ffreestanding -fdata-sections -ffunction-sections")
set(CMAKE_CXX_FLAGS_INIT "${TARGET_CPU_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")
set(CMAKE_ASM_FLAGS_INIT "${TARGET_CPU_FLAGS} -x assembler-with-cpp -MMD -MP")

set(CMAKE_EXE_LINKER_FLAGS_INIT "${TARGET_CPU_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} --specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,--print-memory-usage")
