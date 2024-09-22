add_executable(${PROJECT_NAME}
    src/main.cpp
    src/flow_selector.cpp
    src/usb_manager.cpp
    src/i2c_worker.cpp
    src/logger.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    inc/akolyte/  # TODO
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_multicore
    hardware_i2c
    pico_i2c_slave
    hardware_pio
    tinyusb # TODO: remove
    tinyusb_board # TODO: remove
    tinyusb_device # TODO: remove
    ssd1306
    i2c_driver
    keypad
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})