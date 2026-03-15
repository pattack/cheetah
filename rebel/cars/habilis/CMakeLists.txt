include(src/hal/CMakeLists.txt)

add_library(car_habilis INTERFACE)
target_compile_definitions(car_habilis INTERFACE ${CAR_HAL_DEFINES})
target_include_directories(car_habilis INTERFACE
        ${CAR_HAL_INCLUDES}
        include
)
target_sources(car_habilis INTERFACE
        $<TARGET_OBJECTS:car_hal>
        src/device/gpio.cpp
        src/device/usart.cpp
        src/device/i2c_bus.cpp
        src/device/i2c_device.cpp
        src/device/spi.cpp
        src/device/timer.cpp
        src/device/adc.cpp

        src/component/stdio.cpp
        src/component/pca9685.cpp

        src/module/engine.cpp
        src/module/logger.cpp

        src/store.cpp
        src/factory.cpp
        src/car.cpp
)
target_link_libraries(car_habilis INTERFACE m rebellion)
