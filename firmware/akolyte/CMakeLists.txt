set(LEFT_SIDE "${PROJECT_NAME}_left")

add_executable(${LEFT_SIDE}
    src/main.cpp
    src/core1.cpp
    src/flow_selector.cpp
    src/usb_manager.cpp
    src/i2c_worker.cpp
)

target_include_directories(${LEFT_SIDE} PRIVATE
    inc/
)

target_link_libraries(${LEFT_SIDE}
    pico_stdlib
    pico_multicore
    tinyusb
    ssd1306
    keypad
    queue
    defs_left
    communication
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${LEFT_SIDE})

set(RIGHT_SIDE "${PROJECT_NAME}_right")

add_executable(${RIGHT_SIDE}
    src/main.cpp
    src/core1.cpp
    src/flow_selector.cpp
    src/usb_manager.cpp
    src/i2c_worker.cpp
)

target_include_directories(${RIGHT_SIDE} PRIVATE
    inc/
)

target_link_libraries(${RIGHT_SIDE}
    pico_stdlib
    pico_multicore
    tinyusb
    ssd1306
    keypad
    queue
    defs_right
    communication
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${RIGHT_SIDE})
