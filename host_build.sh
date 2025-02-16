rm -rf host-build
mkdir host-build
cd host-build
cmake -DPICO_PLATFORM=host -DPICO_SDK_PATH=$PICO_SDK_PATH -DPICO_EXTRAS_PATH=$PICO_EXTRAS_PATH -DPICO_SDK_PRE_LIST_DIRS=$PICO_HOST_SDL_PATH .. --trace-source=CMakeLists.txt