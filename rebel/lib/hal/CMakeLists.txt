add_library(hal INTERFACE)

target_include_directories(hal INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Example compile definitions or options
# target_compile_definitions(car PRIVATE SOME_MACRO=1)