add_library(defs INTERFACE)

target_include_directories(defs INTERFACE
    inc/
)

target_link_libraries(defs INTERFACE
    pico_stdlib
    hardware_i2c
)