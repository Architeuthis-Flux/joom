#include "ssd1306_70_40.hpp"
#include "pico/ssd1306.h"
#include "shared.h"



    // .spi      = PICO_DEFAULT_SPI_INSTANCE,
    // .gpio_din = PICO_DEFAULT_SPI_TX_PIN,
    // .gpio_clk = PICO_DEFAULT_SPI_SCK_PIN,
    // .gpio_cs  = PICO_DEFAULT_SPI_CSN_PIN,
    // .gpio_dc  = 20,
    // .gpio_rst = 21,
    // .gpio_bl  = 22,
#define START_Y 24
// +3 to center on 70 pixel width screen
#define START_X (28 + 3)

extern "C" {

    static int16_t dithering_quant_error[DOWNSAMPLED_WIDTH] = {0};
    // we're doing dithering with only a single line buffer, representing the quant error of the _next_ line as we go through
    // the current line. However while we're going through the current line, it's still full of the values that line needs
    // this doesn't cause any issues until we get to the bottom right pixel, which will screw up the next pixel in the current
    // line. so we keep one extra uint16_t that represents this pixel, with 0 as a guard. it's a great guard, because if
    // the quant is actually 0, it can be safely ignored.
     static int16_t bottom_left_dithering_quant_error = 0;
    // shit we need one for the next pixel too since the downscaled line is in color... 
    static int16_t next_pixel_dithering_quant_error = 0;
    static SSD1306* display;

    void ssd1306_70_40_initScreen(void) {
        display = new SSD1306(128, 64, PICO_DEFAULT_SPI_INSTANCE, /*baudrate*/ 8000 * 1000, /*mosi*/ PICO_DEFAULT_SPI_TX_PIN, /*cs*/ PICO_DEFAULT_SPI_CSN_PIN, /*sclk*/ PICO_DEFAULT_SPI_SCK_PIN, /*reset*/ 21, /*dc*/ 20);
        display->init();    

        // for(int y = 24; y < 64; y++) {
        //     for(int x = 28; x < 98; x+=3) {
        //         display->draw_pixel(x, y, SSD1306_COLOR_ON);        
        //     }
        // }
        
        // display->draw_pixel(0, 0, SSD1306_COLOR_ON);
        // display->draw_pixel(135, 120, SSD1306_COLOR_ON);
        // display->draw_pixel(40, 70, SSD1306_COLOR_ON);

        // display->update();

        // sleep_ms(1000);
        // return display;
    }

    void ssd1306_70_40_handleFrameStart(uint8_t frame) {
        memset(dithering_quant_error, 0, sizeof(dithering_quant_error));
        bottom_left_dithering_quant_error = 0;
        next_pixel_dithering_quant_error = 0;
        nearestNeighborHandleFrameStart();
    }

    SSD1306PixelColor greyscaleToColorCodes(uint16_t greyscale) {
        if (greyscale > 127) {
            return SSD1306_COLOR_ON;
        }

        return SSD1306_COLOR_OFF;
    }

    void ditherDownsampledLine(uint16_t *line) {
        // I've had to be careful about 8 vs 16 when going through lines because 320 doesn't fit in 8
        // but we will only be dithering downsampled lines
        // you can just ignore the border pixels to fix off by one errors
        for (uint8_t x = 1; x < DOWNSAMPLED_WIDTH-1; x++) {
            int16_t greyscale = colorToGreyscale(line[x]) + next_pixel_dithering_quant_error + dithering_quant_error[x];
            
            // for safety's sake
            next_pixel_dithering_quant_error = 0;
            dithering_quant_error[x] = 0;

            uint8_t monochrome = greyscale > 127 ? 255 : 0;

            // reassign to line as output
            line[x] = monochrome;

            int16_t quant_error = (greyscale - monochrome);
            // >> 4 == / 16
            // we add the top-right pixel's quant error directly to the next pixel
            line[x+1] += (quant_error * 7) /16;
            next_pixel_dithering_quant_error = (quant_error * 3) /16;
            // here's where that bottom left pixel I was talkin about comes in
            // we can just straight assign - we zeroed this out earlier. yeah it's double jeopardy so what
            dithering_quant_error[x] = bottom_left_dithering_quant_error + ((quant_error * 5) /16);
            bottom_left_dithering_quant_error = quant_error /16;
        }
    }

    void ssd1306_70_40_downsample_y_and_blit(uint16_t* downsampled_line, int scanline) {
        // this converts the line to "monochrome" greyscale
        // ditherDownsampledLine(downsampled_line);
        for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
            uint16_t downsampled_pixel = downsampled_line[x];
            
            // comment out if using dithering
            downsampled_pixel = colorToGreyscale(downsampled_pixel);

            SSD1306PixelColor color = greyscaleToColorCodes(downsampled_pixel);
            display->draw_pixel(START_X + x, START_Y + scanline, color);
        }
        display->update();
    }


    void ssd1306_70_40_handleScanline(uint16_t *line, int scanline) {
        nearestNeighborHandleDownsampling(line, scanline, ssd1306_70_40_downsample_y_and_blit);
    }

    void ssd1306_70_40_handleFrameEnd(uint8_t frame) {
        display->update();
    }
}