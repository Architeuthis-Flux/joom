add_library(doom INTERFACE)
cmake_policy(SET CMP0076 NEW)
# set(SKIP_PICO_STDIO_USB 1)

pico_sdk_init()

target_sources(doom INTERFACE

# usb_descriptors.c  
# board_api.h
            am_map.c        am_map.h
            deh_ammo.c
            deh_bexstr.c
            deh_cheat.c
            deh_doom.c
            deh_frame.c
            deh_misc.c      deh_misc.h
            deh_ptr.c
            deh_sound.c
            deh_thing.c
            deh_weapon.c
                            d_englsh.h
            d_items.c       d_items.h
            d_main.c        d_main.h
            d_net.c
                            doomdata.h
            doomdef.c       doomdef.h
            doomstat.c      doomstat.h
                            d_player.h
            dstrings.c      dstrings.h
                            d_textur.h
                            d_think.h
            f_finale.h
            f_finale.c
            f_wipe.c
            f_wipe.h
            g_game.c        g_game.h
            hu_lib.c        hu_lib.h
            hu_stuff.c      hu_stuff.h
            info.c          info.h
            m_menu.c        m_menu.h
            m_random.c      m_random.h
            p_ceilng.c
            p_doors.c
            p_enemy.c
            p_floor.c
            p_inter.c       p_inter.h
            p_lights.c
                            p_local.h
            p_map.c
            p_maputl.c
            p_mobj.c        p_mobj.h
            p_plats.c
            p_pspr.c        p_pspr.h
            p_saveg.c       p_saveg.h
            p_setup.c       p_setup.h
            p_sight.c
            p_spec.c        p_spec.h
            p_switch.c
            p_telept.c
            p_tick.c        p_tick.h
            p_user.c
            r_bsp.c         r_bsp.h
            r_data_whd.c
            r_data.c        r_data.h
                            r_defs.h
            r_draw.c        r_draw.h
                            r_local.h
            r_main.c        r_main.h
            r_plane.c       r_plane.h
            r_segs.c        r_segs.h
            r_sky.c         r_sky.h
                            r_state.h
            r_things.c      r_things.h
            s_sound.c       s_sound.h
            sounds.c        sounds.h
            statdump.c      statdump.h
            st_lib.c        st_lib.h
            st_stuff.c      st_stuff.h
            wi_stuff.c      wi_stuff.h
)

target_include_directories(doom INTERFACE "../" "${CMAKE_CURRENT_BINARY_DIR}/../../"
${PICO_SDK_PATH}/src/rp2_common/pico_stdio_usb/include
${CMAKE_CURRENT_LIST_DIR}
)

target_compile_definitions(doom INTERFACE
    DOOM_TINY=1

    # TUSB_OPT_DEVICE_ENABLED=1
    # PICO_RP2350=1
    # CFG_TUSB_CONFIG_FILE="tusb_config2.h"
    # NO_USE_MOUSE=1
    # PICO_AUDIO_I2S_PIO=1
    # PICO_AUDIO_I2S_DMA_IRQ=1
    # PICO_USE_SW_SPIN_LOCKS=0
    # PICO_USE_STACK_GUARDS=0
)

if (NOT PICO_SDK)
    target_link_libraries(doom INTERFACE SDL2::SDL2 SDL2::mixer SDL2::net)
else()
    target_link_libraries(doom INTERFACE pico_stdlib pico_multicore tinyusb_device tinyusb_board pico_unique_id)
        # pico_add_extra_outputs(doom)
        # pico_enable_stdio_usb(doom 1)
        # pico_enable_stdio_uart(doom 0)
endif()
