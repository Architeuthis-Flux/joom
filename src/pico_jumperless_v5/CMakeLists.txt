cmake_minimum_required(VERSION 3.12)

# initialize pico_sdk from GIT
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(pico_jumperless_v5)

# initialize the Pico SDK
pico_sdk_init()


add_library(pico_jumperless_v5 INTERFACE)

target_sources(pico_jumperless_v5 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/jumperless_v5.c
)

target_include_directories(pico_jumperless_v5 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/include/
)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(pico_jumperless_v5 1)
    pico_enable_stdio_uart(pico_jumperless_v5 0)


target_link_libraries(pico_jumperless_v5 INTERFACE pico_stdlib hardware_i2c hardware_gpio hardware_pio)
