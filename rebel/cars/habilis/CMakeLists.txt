include(src/hal/CMakeLists.txt)

add_library(car_habilis INTERFACE)
target_compile_definitions(car_habilis INTERFACE ${CAR_HAL_DEFINES})
target_include_directories(car_habilis INTERFACE
        ${CAR_HAL_INCLUDES}
        include
)
target_sources(car_habilis INTERFACE
        $<TARGET_OBJECTS:car_hal>
        src/car/car_factory.cpp
        src/car/habilis.cpp
        src/car/i2c_bus.cpp
        src/car/i2c_device.cpp
        src/toolkit/store.cpp
        src/toolkit/usart_logger.cpp
)
target_link_libraries(car_habilis INTERFACE m car)
