// DESCRIPTION:
// LED / LCD screen-specific logic

#ifndef __SSD1306_70_40_i2c__
#define __SSD1306_70_40_i2c__

#include "shared.h"
#include "pico.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"


#include <stdlib.h>

void ssd1306_70_40_i2c_initScreen(void);
void ssd1306_70_40_i2c_handleScanline(uint16_t *line, int scanline);
void ssd1306_70_40_i2c_handleFrameStart(uint8_t frame);
void ssd1306_70_40_i2c_handleFrameEnd(uint8_t frame);

#endif