add_library(toolkit
        src/virtual.cpp
)

target_include_directories(toolkit PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)