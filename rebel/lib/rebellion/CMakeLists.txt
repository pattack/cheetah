add_library(rebellion INTERFACE)

target_include_directories(rebellion INTERFACE
        include
)

target_sources(rebellion INTERFACE
        src/rebellion/bus.cpp
        src/rebellion/system.cpp
)