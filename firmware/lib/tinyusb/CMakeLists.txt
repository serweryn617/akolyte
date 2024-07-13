add_library(tinyusb STATIC
    src/tinyusb.cpp
    src/usb_descriptors.c
    src/tinyusb_cb.c
)

target_include_directories(tinyusb PUBLIC
    inc/
)

target_link_libraries(tinyusb PRIVATE
    pico_stdlib
    tinyusb_board
    tinyusb_device
)
