add_library(ssd1306 STATIC
    src/ssd1306.cpp
)

target_include_directories(ssd1306 PUBLIC
    inc/
)

target_link_libraries(ssd1306 PRIVATE
    pico_stdlib
    i2c_driver
)
