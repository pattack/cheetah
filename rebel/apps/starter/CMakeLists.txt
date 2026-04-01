add_library(app_starter)

target_include_directories(app_starter PUBLIC
        include
)
target_sources(app_starter PUBLIC
        src/rebel/system.cpp

        src/starter/application/movement.cpp
)
target_link_libraries(app_starter PUBLIC rebel)