set(STM32CUBE_DIR "${CMAKE_SOURCE_DIR}/vendor/stm32cubef4")
# Only download if directory doesn't exist
if (NOT EXISTS "${STM32CUBE_DIR}")
    message(STATUS "Downloading STM32CubeF4...")
    execute_process(
            COMMAND git clone --depth 1 --branch v1.28.3 --recurse-submodules
            https://github.com/STMicroelectronics/STM32CubeF4.git
            "${STM32CUBE_DIR}"
            RESULT_VARIABLE GIT_RESULT
    )
    if (NOT GIT_RESULT EQUAL "0")
        message(FATAL_ERROR "Failed to clone STM32CubeF4")
    endif ()
endif ()

set(STM32_HAL_DIR "${STM32CUBE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src")
file(GLOB STM32_HAL_SOURCES "${STM32_HAL_DIR}/stm32f4xx_hal*.c")
list(FILTER STM32_HAL_SOURCES EXCLUDE REGEX "_template\\.c$")

set(CAR_HAL_DEFINES USE_HAL_DRIVER STM32F401xE)
set(CAR_HAL_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${STM32CUBE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
        ${STM32CUBE_DIR}/Drivers/CMSIS/Include
        ${STM32CUBE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
)
set(CAR_HAL_LOWLEVEL_SOURCES
        ${STM32CUBE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
        src/isr.c
        src/hal_msp.c
        src/sysmem.c
        src/syscalls.c
        src/startup.s
)

add_library(car_hal OBJECT)
target_compile_definitions(car_hal PRIVATE ${CAR_HAL_DEFINES})
target_include_directories(car_hal PRIVATE ${CAR_HAL_INCLUDES})
target_sources(car_hal PRIVATE
        ${STM32_HAL_SOURCES}
        ${CAR_HAL_LOWLEVEL_SOURCES}
)
target_compile_options(car_hal PRIVATE
        -O0
        -mno-unaligned-access
        # -fno-inline
        -fno-tree-sra
        -fno-ipa-sra
)

add_library(car_habilis INTERFACE)
target_compile_definitions(car_habilis INTERFACE ${CAR_HAL_DEFINES})
target_include_directories(car_habilis INTERFACE ${CAR_HAL_INCLUDES})
target_sources(car_habilis INTERFACE
        $<TARGET_OBJECTS:car_hal>
        src/car/car_factory.cpp
        src/car/habilis.cpp
        src/car/i2c_bus.cpp
        src/car/i2c_device.cpp
        src/toolkit/store.cpp
        src/toolkit/usart_logger.cpp
)
target_link_libraries(car_habilis INTERFACE m car)
