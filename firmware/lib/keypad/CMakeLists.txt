add_library(keypad STATIC
    src/keypad.cpp
)

target_include_directories(keypad PUBLIC
    inc/
)

target_link_libraries(keypad PUBLIC
    defs_base
)

target_link_libraries(keypad PRIVATE
    pico_stdlib
)
