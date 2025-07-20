add_library(app
        src/main.cpp
)

target_include_directories(app PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Example compile definitions or options
# target_compile_definitions(car PRIVATE SOME_MACRO=1)