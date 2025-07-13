# Generic ARM Cortex-M3 toolchain for STM32F103 (Blue Pill)

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

# Target CPU options
set(TARGET_CPU_FLAGS "-mcpu=cortex-m3 -mthumb")

# No standard libraries
set(CMAKE_C_FLAGS_INIT "${TARGET_CPU_FLAGS} -ffreestanding")
set(CMAKE_CXX_FLAGS_INIT "${TARGET_CPU_FLAGS} -fno-rtti -fno-exceptions")
set(CMAKE_ASM_FLAGS_INIT "${TARGET_CPU_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${TARGET_CPU_FLAGS} -nostdlib")

# Bypass default linker
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
