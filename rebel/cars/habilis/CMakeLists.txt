include(src/habilis/hal/CMakeLists.txt)

add_library(car_habilis INTERFACE)
target_compile_definitions(car_habilis INTERFACE ${CAR_HAL_DEFINES})
target_include_directories(car_habilis INTERFACE
        ${CAR_HAL_INCLUDES}
        include
)
target_sources(car_habilis INTERFACE
        $<TARGET_OBJECTS:car_hal>

        src/rebel/system.cpp
        src/rebel/io/text/logger.cpp

        src/habilis/kit.cpp
        src/habilis/device/gpio.cpp
        src/habilis/device/usart.cpp
        src/habilis/device/i2c.cpp
        src/habilis/device/spi.cpp
        src/habilis/device/timer.cpp
        src/habilis/device/adc.cpp

        src/habilis/component/ads1110.cpp
        src/habilis/component/led.cpp
        src/habilis/component/stdio.cpp
        src/habilis/component/pca9685.cpp

        src/habilis/module/accelerator.cpp
        src/habilis/module/engine.cpp
        src/habilis/module/indicator.cpp

        src/habilis/io/text/logger.cpp

        src/habilis/car.cpp
)
target_link_libraries(car_habilis INTERFACE m rebel)
