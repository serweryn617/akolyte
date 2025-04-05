add_library(defs_base INTERFACE)

target_include_directories(defs_base INTERFACE
    inc/
)


add_library(defs_left INTERFACE)

target_include_directories(defs_left INTERFACE
    inc/
    left/
)

target_link_libraries(defs_left INTERFACE
    pico_stdlib
    hardware_i2c
)


add_library(defs_right INTERFACE)

target_include_directories(defs_right INTERFACE
    inc/
    right/
)

target_link_libraries(defs_right INTERFACE
    pico_stdlib
    hardware_i2c
)
