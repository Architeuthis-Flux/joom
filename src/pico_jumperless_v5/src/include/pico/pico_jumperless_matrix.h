/* Example code to talk to an SSD1306-based OLED display

   The SSD1306 is an OLED/PLED driver chip, capable of driving displays up to
   128x64 pixels.

   NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Pico
   GPIO (and therefore I2C) cannot be used at 5v.

   You will need to use a level shifter on the I2C lines if you want to run the
   board at 5v.

   Connections on Raspberry Pi Pico board, other boards may vary.

   GPIO PICO_DEFAULT_I2C_SDA_PIN (on Pico this is GP4 (pin 6)) -> SDA on display
   board
   GPIO PICO_DEFAULT_I2C_SCL_PIN (on Pico this is GP5 (pin 7)) -> SCL on
   display board
   3.3v (pin 36) -> VCC on display board
   GND (pin 38)  -> GND on display board
*/

#ifndef JMATRIX_H
#define JMATRIX_H

// Define the size of the display we have attached. This can vary, make sure you
// have the right size defined or the output will look rather odd!
// Code has been tested on 128x32 and 128x64 OLED displays
#define JMATRIX_HEIGHT              14
#define JMATRIX_WIDTH               30

#define JMATRIX_MEMORY_HEIGHT       20
#define JMATRIX_MEMORY_WIDTH        30


// #include "shared.h"
#include "pico.h"

#include "pico/binary_info.h"
#include "pico/stdlib.h"


#include <stdlib.h>


#define MEMORY_WIDTH 60
#define MEMORY_HEIGHT 20

#define LCD_WIDTH 30
#define LCD_HEIGHT 14

#define SCREEN_WIDTH_OFFSET ((LCD_WIDTH - (SCREENWIDTH * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100)) / 2)


// void jumperless_initScreen(void);
// void jumperless_handleScanline(uint16_t *line, int scanline);
// void jumperless_handleFrameStart(uint8_t frame);
// void jumperless_handleFrameEnd(uint8_t frame);



#endif