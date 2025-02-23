

# set(SKIP_PICO_STDIO_USB 1)
add_library(common_pico INTERFACE)

target_sources(common_pico INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/i_glob.c
        ${CMAKE_CURRENT_LIST_DIR}/i_input.c
        ${CMAKE_CURRENT_LIST_DIR}/i_system.c
        $<$<BOOL:${USE_PICO_NET}>:${CMAKE_CURRENT_LIST_DIR}/piconet.c>
        
        ${CMAKE_CURRENT_LIST_DIR}/i_timer.c
        ${CMAKE_CURRENT_LIST_DIR}/i_video.c
        ${CMAKE_CURRENT_LIST_DIR}/stubs.c

        ${CMAKE_CURRENT_LIST_DIR}/i_picosound.c

        ${CMAKE_CURRENT_LIST_DIR}/pico-screens/screens/shared.c
        ${CMAKE_CURRENT_LIST_DIR}/pico-screens/screen.c
        ${CMAKE_CURRENT_LIST_DIR}/pico-screens/screens/lilygo_ttgo.c
        ${CMAKE_CURRENT_LIST_DIR}/pico-screens/screens/st7789_240_135.c
        ${CMAKE_CURRENT_LIST_DIR}/pico-screens/screens/ssd1306_70_40.cpp
        ${CMAKE_CURRENT_LIST_DIR}/pico-screens/screens/ssd1306_70_40_i2c.c
        ${CMAKE_CURRENT_LIST_DIR}/pico-screens/screens/st7735_128_128.c
        ${CMAKE_CURRENT_LIST_DIR}/pico-screens/screens/jumperless_v5.c
        ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
 ${CMAKE_CURRENT_LIST_DIR}/stdio_usb.c
)
if (PICO_ON_DEVICE)
    target_sources(common_pico INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/blit.S
            ${CMAKE_CURRENT_LIST_DIR}/picoflash.c
            )
    pico_wrap_function(common_pico malloc)
    pico_wrap_function(common_pico calloc)
    pico_wrap_function(common_pico free)
    target_compile_definitions(common_pico INTERFACE
            PICO_HEAP_SIZE=0
            USE_ZONE_FOR_MALLOC=1
    )
    target_link_libraries(common_pico INTERFACE  hardware_i2c)
endif()
target_include_directories(common_pico INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/..
        ${CMAKE_CURRENT_LIST_DIR}/../../textscreen
        
        )

target_compile_definitions(common_pico INTERFACE
 TUSB_OPT_DEVICE_ENABLED=1
# PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1
# PICO_RP2040_USB_DEVICE_UFRAME_FIX=1
 PICO_RP2350=1
 CFG_TUSB_CONFIG_FILE="tusb_config2.h"
  DOOM_TINY=1
# PICO_STDIO_USB_LOW_PRIORITY_IRQ=1

#   CFG_TUD_CDC=3
        NO_USE_MOUSE=1
        PICO_AUDIO_I2S_PIO=1
        PICO_AUDIO_I2S_DMA_IRQ=1
        PICO_USE_SW_SPIN_LOCKS=0
        PICO_USE_STACK_GUARDS=0 # todo we can actually use these sensibly, but right now we do overflow!
)

target_link_libraries(common_pico INTERFACE pico_stdlib pico_multicore pico_scanvideo_dpi tinyusb_device )

add_library(pico_cd INTERFACE)

target_compile_definitions(pico_cd INTERFACE
#  TUSB_OPT_DEVICE_ENABLED=1
#  CFG_TUD_CDC=6
# TUSB_OPT_HOST_ENABLED=1

)


# if (TARGET tinyusb_host)
#     target_link_libraries(pico_cd INTERFACE tinyusb_device)
#  endif()
# pico_enable_stdio_usb(common_pico 1)
# pico_enable_stdio_uart(common_pico 0)
# pico_enable_stdio_usb(pico_cd 1)
# pico_enable_stdio_uart(pico_cd 0)

#  set(PROJECT hello)
# cmake_minimum_required(VERSION 3.12)
# include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
# project(${PROJECT} C CXX)
# pico_sdk_init()
# add_executable(${PROJECT} i_input.c)
# target_link_libraries(${PROJECT} pico_stdlib)
# pico_add_extra_outputs(${PROJECT})
# pico_enable_stdio_usb(${PROJECT} 1)
# pico_enable_stdio_uart(${PROJECT} 0)
