add_library(app_starter)

target_sources(app_starter PRIVATE
        src/main.cpp
)

target_include_directories(car_habilis PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(app_starter PUBLIC app)