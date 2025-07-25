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

set(stm32cubef1_SOURCE_DIR "${STM32CUBE_DIR}")

target_compile_definitions(car_habilis PUBLIC STM32F103x6)

file(GLOB HAL_DRIVER_SOURCES "${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/*.c")
target_sources(car_habilis PRIVATE
        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c
        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c

        ${stm32cubef1_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c

        src/car/isr.cpp
        src/car/habilis.cpp
        src/car/car_factory.cpp
        src/car/i2c_bus.cpp

        src/toolkit/store.cpp
        src/toolkit/usart_logger.cpp
)

target_include_directories(car_habilis PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include

        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc

        ${stm32cubef1_SOURCE_DIR}/Drivers/CMSIS/Include
        ${stm32cubef1_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include
)

target_link_libraries(car_habilis PUBLIC car)