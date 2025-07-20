add_library(car
        src/car_factory.cpp
)

target_include_directories(car PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Example compile definitions or options
# target_compile_definitions(car PRIVATE SOME_MACRO=1)