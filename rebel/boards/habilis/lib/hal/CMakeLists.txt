add_library(hal_habilis)

include(FetchContent)
FetchContent_Declare(
        stm32cubef1
        GIT_REPOSITORY https://github.com/STMicroelectronics/STM32CubeF1.git
        GIT_TAG v1.8.6
)
FetchContent_MakeAvailable(stm32cubef1)

target_compile_definitions(hal_habilis PUBLIC STM32F103x6)

target_sources(hal_habilis PRIVATE
        src/i2c_bus.cpp
        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c
        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
)

target_include_directories(hal_habilis PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${stm32cubef1_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc
        ${stm32cubef1_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include
        ${stm32cubef1_SOURCE_DIR}/Drivers/CMSIS/Include
)

target_link_libraries(hal_habilis PUBLIC hal)