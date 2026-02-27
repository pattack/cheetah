add_library(car_habilis INTERFACE)
add_library(car_habilis_hal OBJECT)

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

target_compile_definitions(car_habilis INTERFACE USE_HAL_DRIVER STM32F401xE)
target_compile_definitions(car_habilis_hal PRIVATE USE_HAL_DRIVER STM32F401xE)

set(STM32_HAL_DIR "${STM32CUBE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src")
target_sources(car_habilis_hal PRIVATE
        ${STM32_HAL_DIR}/stm32f4xx_hal.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_cortex.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_dma.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_dma_ex.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_exti.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_flash.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_flash_ex.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_flash_ramfunc.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_gpio.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_i2c.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_i2c_ex.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_pwr.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_pwr_ex.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_rcc.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_rcc_ex.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_uart.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_usart.c

        ${STM32CUBE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c

        src/isr.c
        src/hal_msp.c
        src/sysmem.c
        src/syscalls.c
        src/startup.s
)

set(HAL_GPIO_SOURCE "${STM32_HAL_DIR}/stm32f4xx_hal_gpio.c")
set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hal_msp.c
        ${HAL_GPIO_SOURCE}
        PROPERTIES COMPILE_OPTIONS "-O0;-mno-unaligned-access;-fno-inline;-fno-tree-sra;-fno-ipa-sra"
)

target_include_directories(car_habilis_hal PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include

        ${STM32CUBE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc

        ${STM32CUBE_DIR}/Drivers/CMSIS/Include
        ${STM32CUBE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
)

target_sources(car_habilis INTERFACE
        $<TARGET_OBJECTS:car_habilis_hal>
        src/car/car_factory.cpp
        src/car/habilis.cpp
        src/car/i2c.cpp

        src/toolkit/store.cpp
        src/toolkit/usart_logger.cpp
)

target_include_directories(car_habilis INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include

        ${STM32CUBE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc

        ${STM32CUBE_DIR}/Drivers/CMSIS/Include
        ${STM32CUBE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
)

target_link_libraries(car_habilis INTERFACE m car)
