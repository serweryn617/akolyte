add_executable(${PROJECT_NAME}
    src/main.cpp
    src/core1.cpp
    src/flow_selector.cpp
    src/usb_manager.cpp
    src/i2c_worker.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    inc/
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_multicore
    tinyusb
    ssd1306
    keypad
    queue
    defs
    communication
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})
