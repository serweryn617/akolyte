add_library(logger STATIC
    src/logger.cpp
)

target_include_directories(logger PUBLIC
    inc/
)

target_link_libraries(logger PRIVATE
    pico_stdlib
    hardware_uart
)
