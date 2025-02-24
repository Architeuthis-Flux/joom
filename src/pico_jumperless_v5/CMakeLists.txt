cmake_minimum_required(VERSION 3.12)

# initialize pico_sdk from GIT
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()


#  set(SKIP_PICO_STDIO_USB 1)

include(pico_sdk_import.cmake)

project(pico_jumperless_v5)

# initialize the Pico SDK
pico_sdk_init()


add_library(pico_jumperless_v5 INTERFACE)


target_sources(pico_jumperless_v5 INTERFACE
${CMAKE_CURRENT_LIST_DIR}/src/jumperless_v5.c    
${CMAKE_CURRENT_LIST_DIR}/src/RotaryEncoderStuff.c
${CMAKE_CURRENT_LIST_DIR}/src/probing.c

)

target_include_directories(pico_jumperless_v5 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/include/
    ${CMAKE_CURRENT_LIST_DIR}/../
    ${CMAKE_CURRENT_LIST_DIR}
    # ${PICO_SDK_PATH}/src/rp2_common/pico_stdio_usb/include
)
target_compile_definitions(pico_jumperless_v5 INTERFACE
    PICO_RP2350=1
  )



target_link_libraries(pico_jumperless_v5 INTERFACE 
pico_stdlib 
hardware_i2c 
hardware_gpio 
hardware_pio 
hardware_timer
pico_time


# tinyusb_device 
# tinyusb_board
pico_unique_id)


    # enable usb output, disable uart output
    # # pico_add_extra_outputs(pico_jumperless_v5)
    # pico_enable_stdio_usb(pico_jumperless_v5 1)
    # pico_enable_stdio_uart(pico_jumperless_v5 0)
