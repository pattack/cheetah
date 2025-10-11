add_library(car_habilis)

set(STM32CUBE_DIR "${CMAKE_SOURCE_DIR}/vendor/stm32cubef1")

# Only download if directory doesn't exist
if (NOT EXISTS "${STM32CUBE_DIR}")
    message(STATUS "Downloading STM32CubeF1...")
    execute_process(
            COMMAND git clone --depth 1 --branch v1.8.6 --recurse-submodules
            https://github.com/STMicroelectronics/STM32CubeF1.git
            "${STM32CUBE_DIR}"
            RESULT_VARIABLE GIT_RESULT
    )
    if (NOT GIT_RESULT EQUAL "0")
        message(FATAL_ERROR "Failed to clone STM32CubeF1")
    endif ()
endif ()

target_compile_definitions(car_habilis PUBLIC STM32F103x6)

set(STM32_HAL_DIR "${STM32CUBE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src")
file(GLOB HAL_DRIVER_SOURCES "${STM32_HAL_DIR}/*.c")
target_sources(car_habilis PUBLIC
        ${STM32_HAL_DIR}/stm32f1xx_hal.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_cortex.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_dma.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_exti.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_flash.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_flash_ex.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_gpio.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_gpio_ex.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_i2c.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_pwr.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_rcc.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_rcc_ex.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_uart.c
        ${STM32_HAL_DIR}/stm32f1xx_hal_usart.c

        ${STM32CUBE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c

        src/car/car_factory.cpp
        src/car/habilis.cpp
        src/car/i2c.cpp

        src/toolkit/store.cpp
        src/toolkit/usart_logger.cpp

        src/syscalls.c
        src/sysmem.c
        src/hal_msp.c
        src/isr.cpp
        src/startup.s
)

target_include_directories(car_habilis PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include

        ${STM32CUBE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc

        ${STM32CUBE_DIR}/Drivers/CMSIS/Include
        ${STM32CUBE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include
)

target_link_libraries(car_habilis PUBLIC m car)