add_library(car
        src/car_factory.cpp
)

target_include_directories(car PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(car PUBLIC toolkit)