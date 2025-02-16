// DESCRIPTION:
// LED / LCD screen-specific logic

#ifndef __SSD1306_70_40__
#define __SSD1306_70_40__

#include "shared.h"
#include "pico.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void ssd1306_70_40_initScreen(void);
void ssd1306_70_40_handleScanline(uint16_t *line, int scanline);
void ssd1306_70_40_handleFrameStart(uint8_t frame);
void ssd1306_70_40_handleFrameEnd(uint8_t frame);


#ifdef __cplusplus
}
#endif

#endif