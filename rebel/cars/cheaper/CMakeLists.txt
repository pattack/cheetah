add_library(car_cheaper INTERFACE)
target_include_directories(car_cheaper INTERFACE
        include
)
target_sources(car_cheaper INTERFACE
        src/rebel/system.cpp
        src/rebel/io/mod/logger.cpp

        src/cheaper/driver.cpp
)
target_link_libraries(car_cheaper INTERFACE m rebel)