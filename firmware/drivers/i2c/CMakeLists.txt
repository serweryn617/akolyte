add_library(i2c_driver STATIC
    src/i2c_driver.cpp
)

target_include_directories(i2c_driver PUBLIC
    inc/
)

# TODO: Why public include?
target_link_libraries(i2c_driver PUBLIC
    hardware_i2c
)

target_link_libraries(i2c_driver PRIVATE
    pico_i2c_slave
    pico_stdlib
)