add_library(hal_stm32f103)

target_sources(hal_stm32f103 PRIVATE
        src/i2c_bus.cpp
)

target_include_directories(hal_stm32f103 PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(hal_stm32f103 PUBLIC hal)