# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Export compile commands json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include($ENV{PICO_SDK_PATH}/tools/CMakeLists.txt)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(keypad C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# set(FAMILY rp2040)
# set(BOARD pico_sdk)
# set(TINYUSB_FAMILY_PROJECT_NAME_PREFIX "tinyusb_dev_")
# set(CFG_TUSB_MCU OPT_MCU_RP2040)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/hid_keycodes.cpp
    src/keypad.cpp
    src/led.cpp
    src/flow_selector.cpp
    src/usb_manager.cpp
    src/i2c_worker.cpp
    src/logger.cpp
    drivers/pico/i2c/src/pico_i2c_driver.cpp
)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/pio/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/../build/generated/pio)

target_include_directories(${PROJECT_NAME} PRIVATE
    inc/
    build/generated/pio/
)

add_subdirectory(lib)

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_i2c
    pico_i2c_slave
    hardware_pio
    tinyusb
    tinyusb_board
    tinyusb_device # TODO: Can this be omitted?
)

target_compile_definitions(${PROJECT_NAME} PRIVATE SIDE=${SIDE})

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Enable usb output
# pico_enable_stdio_usb(${PROJECT_NAME} 1)

# Disable uart output, as it uses pins 0 and 1
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})
