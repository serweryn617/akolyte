add_library(crc STATIC
    src/crc.cpp
)

target_include_directories(crc PUBLIC
    inc/
)

target_link_libraries(crc PRIVATE
    pico_stdlib
)
