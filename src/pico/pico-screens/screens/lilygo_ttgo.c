#include "lilygo_ttgo.h"

static const struct st7789_config lcd_config = {
    .spi      = PICO_DEFAULT_SPI_INSTANCE,
    .gpio_din = 3,
    .gpio_clk = 2,
    .gpio_cs  = 5,
    .gpio_dc  = 1,
    .gpio_rst = 0,
    .gpio_bl  = 4,
};

void lilygo_ttgo_initScreen(void) {
    // turning on the backlight
    gpio_init(22);
    gpio_set_dir(22, GPIO_OUT);
    gpio_put(22, 1);
    // width and height only come into play for fills so let's just pass the memory size instead of LCD size
    st7789_init(&lcd_config, MEMORY_WIDTH, MEMORY_HEIGHT);
    st7789_fill(0x0000);
}

void lilygo_ttgo_handleFrameStart(uint8_t frame) {
    nearestNeighborHandleFrameStart();
}

void lilygo_ttgo_blit(uint16_t *downsampled_line, int scanline) {
    // st7789_fill(scanline % 2 == 0 ? 0x0000 : 0xffff);
    st7789_set_cursor((MEMORY_WIDTH - LCD_WIDTH) / 2 + SCREEN_WIDTH_OFFSET, (MEMORY_HEIGHT - LCD_HEIGHT) / 2 + (scanline));
    st7789_write(downsampled_line, sizeof(downsampled_line) * DOWNSAMPLED_WIDTH/2); // no idea why /2
    
    // write() has had some issues... use this instead if you are trying to blit less than a full row
    for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
        // st7789_put(downsampled_line[x]); 
    }
}

void lilygo_ttgo_handleScanline(uint16_t *line, int scanline) {
    nearestNeighborHandleDownsampling(line, scanline, lilygo_ttgo_blit);
}