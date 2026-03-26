add_library(app_starter)

target_sources(app_starter PUBLIC
        src/rebellion/system.cpp

        src/starter/application/movement.cpp
)

target_include_directories(app_starter PUBLIC
        include
)

target_link_libraries(app_starter PUBLIC rebellion)