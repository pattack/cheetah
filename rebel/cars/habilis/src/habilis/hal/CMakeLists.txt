pat_install_dep(
        NAME stm32cubef4
        ADDRESS https://github.com/STMicroelectronics/STM32CubeF4.git
        VERSION v1.28.3

        RES_INSTALL_DIR STM32CUBE_DIR
)

set(CAR_HAL_DEFINES
        USE_HAL_DRIVER
        STM32F401xE
)

set(CAR_HAL_INCLUDES
        ${CMAKE_SOURCE_DIR}/cars/habilis/include
        ${CMAKE_SOURCE_DIR}/lib/rebel/include

        ${STM32CUBE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
        ${STM32CUBE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
        ${STM32CUBE_DIR}/Drivers/CMSIS/Include
)

set(STM32_HAL_DIR "${STM32CUBE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src")
set(CAR_HAL_STM32_HAL_SOURCES
        ${STM32CUBE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
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
        ${STM32_HAL_DIR}/stm32f4xx_hal_spi.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_rcc.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_rcc_ex.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_uart.c
        ${STM32_HAL_DIR}/stm32f4xx_hal_usart.c
)

set(CAR_HAL_LOWLEVEL_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/gpio.cpp
        ${CMAKE_CURRENT_LIST_DIR}/i2c.cpp
        ${CMAKE_CURRENT_LIST_DIR}/spi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/usart.cpp
        ${CMAKE_CURRENT_LIST_DIR}/uart.cpp

        ${CMAKE_CURRENT_LIST_DIR}/isr.cpp
        ${CMAKE_CURRENT_LIST_DIR}/msp.c

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
target_link_libraries(car_hal PRIVATE m)

set(CAR_HAL_DEFINES ${CAR_HAL_DEFINES} PARENT_SCOPE)
set(CAR_HAL_INCLUDES ${CAR_HAL_INCLUDES} PARENT_SCOPE)
