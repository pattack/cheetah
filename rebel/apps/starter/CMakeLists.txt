add_library(app_starter)

target_sources(app_starter PUBLIC
        src/main.cpp
)

target_include_directories(app_starter PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(app_starter PUBLIC app car)