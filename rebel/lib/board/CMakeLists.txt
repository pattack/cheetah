add_library(board
        src/board.cpp
        src/component_registry.cpp
)

target_include_directories(board PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Example compile definitions or options
# target_compile_definitions(car PRIVATE SOME_MACRO=1)