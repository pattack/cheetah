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
        src/rebel/io/mod/logger.cpp

        src/habilis/kit.cpp
        src/habilis/io/dev/adc.cpp
        src/habilis/io/dev/gpio.cpp
        src/habilis/io/dev/i2c.cpp
        src/habilis/io/dev/spi.cpp
        src/habilis/io/dev/timer.cpp
        src/habilis/io/dev/usart.cpp

        src/habilis/io/com/ads1110.cpp
        src/habilis/io/com/ads1115.cpp
        src/habilis/io/com/led.cpp
        src/habilis/io/com/pca9685.cpp

        src/habilis/io/mod/accelerator.cpp
        src/habilis/io/mod/indicator.cpp
        src/habilis/io/mod/logger.cpp

        src/habilis/io/text/usart_printer.cpp

        src/habilis/motion/motor/dc.cpp

        src/habilis/car.cpp
        src/habilis/driver.cpp
)
target_link_libraries(car_habilis INTERFACE m rebel)
