# Generic AVR toolchain for ATTiny25
set(TARGET_MCU "attiny25")
message(STATUS "Target mcu is: ${TARGET_MCU}")

# Target system
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

# Toolchain prefix
set(CROSS_COMPILE avr-)

# Compilers
set(CMAKE_C_COMPILER    ${CROSS_COMPILE}gcc)
set(CMAKE_CXX_COMPILER  ${CROSS_COMPILE}g++)
set(CMAKE_ASM_COMPILER  ${CMAKE_C_COMPILER})
set(CMAKE_LINKER        ${CROSS_COMPILE}g++)
set(CMAKE_OBJCOPY       ${CROSS_COMPILE}objcopy)
set(CMAKE_OBJDUMP       ${CROSS_COMPILE}objdump)
set(CMAKE_SIZE          ${CROSS_COMPILE}size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

# Bypass default linker
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TARGET_CPU_FLAGS "-mmcu=${TARGET_MCU}")
set(TARGET_COMPILE_FLAGS "-ffunction-sections -fdata-sections")

# No standard libraries
set(CMAKE_C_FLAGS_INIT "${TARGET_CPU_FLAGS} ${TARGET_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -fno-rtti -fno-exceptions -fno-threadsafe-statics")
set(CMAKE_ASM_FLAGS_INIT "${TARGET_CPU_FLAGS} -x assembler-with-cpp -MMD -MP")

set(CMAKE_C_FLAGS_DEBUG "-save-temps -g -gdwarf-3 -gstrict-dwarf")
set(CMAKE_CXX_FLAGS_DEBUG "-save-temps -g -gdwarf-3 -gstrict-dwarf")
set(CMAKE_C_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS_RELEASE "")

set(CMAKE_EXE_LINKER_FLAGS_INIT "${TARGET_CPU_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} --specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,-Map=${CMAKE_PROJECT_NAME}.map")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,--print-memory-usage")