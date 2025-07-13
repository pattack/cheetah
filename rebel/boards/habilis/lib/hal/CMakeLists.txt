add_library(hal_habilis)

target_sources(hal_habilis PRIVATE
        src/i2c_bus.cpp
)

target_include_directories(hal_habilis PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(hal_habilis PUBLIC hal)