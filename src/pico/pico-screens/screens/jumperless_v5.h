#ifndef __JUMPERLESSLEDS__
#define __JUMPERLESSLEDS__

#include "shared.h"
#include "pico.h"

#include "pico/binary_info.h"
#include "pico/stdlib.h"


#include <stdlib.h>


#define MEMORY_WIDTH 60
#define MEMORY_HEIGHT 20

#define LCD_WIDTH 30
#define LCD_HEIGHT 14

#define SCREEN_WIDTH_OFFSET ((LCD_WIDTH - (SCREENWIDTH * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100)) / 2)


extern volatile int clickwheelDirection;
extern volatile int clickwheelButton;
extern volatile int probeButton;



void jumperless_initScreen(void);
void jumperless_handleScanline(uint16_t *line, int scanline);
void jumperless_handleFrameStart(uint8_t frame);
void jumperless_handleFrameEnd(uint8_t frame);
void init_clickwheel(void);
int check_clickwheel(void);
void init_probe(void);
void check_probe_button(void);
// void init_sound(void);
// void play_jumperless_sound(int sound);
void jumperless_clearScreen(void);


#endif