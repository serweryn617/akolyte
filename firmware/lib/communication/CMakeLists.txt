add_library(communication STATIC
    src/communication.cpp
)

target_include_directories(communication PUBLIC
    inc/
)

target_link_libraries(communication PUBLIC
    pico_stdlib
    i2c_driver
)
