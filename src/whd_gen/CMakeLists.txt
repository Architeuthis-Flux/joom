if (NOT PICO_ON_DEVICE)
    add_library(wad INTERFACE)
    target_sources(wad INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/wad.cpp)
    target_include_directories(wad INTERFACE ${CMAKE_CURRENT_LIST_DIR})
enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
    add_executable(whd_gen
            whd_gen.cpp
            mus2seq.cpp
            huff.cpp
            lodepng.cpp
            compress_mus.cpp
            ../tiny_huff.c
            ../musx_decoder.c
            ../image_decoder.c
            )

    target_compile_definitions(whd_gen PRIVATE IS_WHD_GEN=1)

    target_include_directories(whd_gen PRIVATE .. ../doom)
    target_link_libraries(whd_gen PRIVATE wad adpcm-lib)
endif()
