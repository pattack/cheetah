set(STM32CUBE_DIR "${CMAKE_SOURCE_DIR}/vendor/stm32cubef4")
# Only download if directory doesn't exist.
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
set(CAR_HAL_STM32_HAL_SOURCES
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
)

set(CAR_HAL_DEFINES
        USE_HAL_DRIVER
        STM32F401xE
)

set(CAR_HAL_INCLUDES
        ${CMAKE_CURRENT_LIST_DIR}/../../include
        ${STM32CUBE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
        ${STM32CUBE_DIR}/Drivers/CMSIS/Include
        ${STM32CUBE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
)

set(CAR_HAL_LOWLEVEL_SOURCES
        ${STM32CUBE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
        ${CMAKE_CURRENT_LIST_DIR}/isr.c
        ${CMAKE_CURRENT_LIST_DIR}/hal_msp.c
        ${CMAKE_CURRENT_LIST_DIR}/sysmem.c
        ${CMAKE_CURRENT_LIST_DIR}/syscalls.c
        ${CMAKE_CURRENT_LIST_DIR}/startup.s
)

add_library(car_hal OBJECT)
target_compile_definitions(car_hal PRIVATE ${CAR_HAL_DEFINES})
target_include_directories(car_hal PRIVATE ${CAR_HAL_INCLUDES})
target_sources(car_hal PRIVATE
        ${CAR_HAL_STM32_HAL_SOURCES}
        ${CAR_HAL_LOWLEVEL_SOURCES}
)

set(CAR_HAL_DEFINES ${CAR_HAL_DEFINES} PARENT_SCOPE)
set(CAR_HAL_INCLUDES ${CAR_HAL_INCLUDES} PARENT_SCOPE)
