add_library(rebel INTERFACE)

target_include_directories(rebel INTERFACE
        include
)

target_sources(rebel INTERFACE
        src/rebel/sys/bus.cpp
        src/rebel/sys/system.cpp
)