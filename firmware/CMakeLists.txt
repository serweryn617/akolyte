# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Export compile commands json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include($ENV{PICO_SDK_PATH}/tools/CMakeLists.txt)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(akolyte C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

add_subdirectory(akolyte)
add_subdirectory(drivers)
add_subdirectory(lib)

# Enable usb output
# pico_enable_stdio_usb(${PROJECT_NAME} 1)

# Disable uart output, as it uses pins 0 and 1
# pico_enable_stdio_uart(${PROJECT_NAME} 0)
