include(src/rebel/habilis/hal/CMakeLists.txt)

add_library(car_habilis INTERFACE)
target_compile_definitions(car_habilis INTERFACE ${CAR_HAL_DEFINES})
target_include_directories(car_habilis INTERFACE
        ${CAR_HAL_INCLUDES}
        include
)
target_sources(car_habilis INTERFACE
        $<TARGET_OBJECTS:car_hal>

        src/rebellion/system.cpp
        src/rebellion/module/logger.cpp

        src/rebel/habilis/kit.cpp
        src/rebel/habilis/device/gpio.cpp
        src/rebel/habilis/device/usart.cpp
        src/rebel/habilis/device/i2c.cpp
        src/rebel/habilis/device/spi.cpp
        src/rebel/habilis/device/timer.cpp
        src/rebel/habilis/device/adc.cpp

        src/rebel/habilis/component/ads1110.cpp
        src/rebel/habilis/component/stdio.cpp
        src/rebel/habilis/component/pca9685.cpp

        src/rebel/habilis/module/accelerator.cpp
        src/rebel/habilis/module/engine.cpp
        src/rebel/habilis/module/logger.cpp

        src/rebel/habilis/service/car.cpp
)
target_link_libraries(car_habilis INTERFACE m rebellion)
