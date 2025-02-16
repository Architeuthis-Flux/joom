#include "pico/pico-screens/screens/jumperless_v5.h"
#include "pico/pico_jumperless_matrix.h"
#include "pico/pico-screens/screens/shared.h"
#include "pico/ws2812.pio.h"

#include "hardware/pio.h"
#include "hardware/clocks.h"

#include <stdlib.h>
#include <stdio.h>
// #include "pico/usb_device.h"
#include "tusb.h"

#define IS_RGBW false
#define WS2812_PIN 17
#define NUM_PIXELS 445

// #define WS2812_PIN_1 17
// #define NUM_PIXELS_1 300

// #define WS2812_PIN_2 3
// #define NUM_PIXELS_2 145


PIO pio;
uint sm;
uint offset;

// Check the pin is compatible with the platform
#if WS2812_PIN >= NUM_BANK0_GPIOS
#error Attempting to use a pin>=32 on a platform that does not support it
#endif

static inline void put_pixel(PIO pio, uint sm, uint32_t pixel_grb) {

    //pixel_grb &= 0x002f1f1f;
    //pixel_grb <<= 8u;
    uint8_t g = (pixel_grb & 0x00ff0000) >> 16;
    uint8_t r = (pixel_grb & 0x0000ff00) >> 8;
    uint8_t b = (pixel_grb & 0x000000ff);

    if (r < 0x5a && g < 0x5a && b < 0x5a) {
        r = 0x00;
        g = 0x00;
        b = 0x00;
    }

    if (r < 0x6a && b < 0x6a) {
        r = 0x00;
        b = 0x00;
    }
    if (r < 0x36) {
        r = 0x00;
    }
    //g = g*32;

    if (b < 0x46) {
        g = b;
        b = 0x00;
        
    }
    
     g = g*8;
    r = r/8;
     b = b/16;

    //  if (g < 0x06) {
    //      g = 0x00;
    //  }

    // pixel_grb &= 0xff000000;
    // pixel_grb |= (g << 16);
    
    
   //pixel_grb |= (r << 8);
     //pixel_grb |= b;



    // if ((pixel_grb & 0x00ff0000 >> 16) < 0x05) {
    //     pixel_grb &= (0xff00ffff);  
    // } 
        
    // if ((pixel_grb & 0x0000ff00 >> 8) < 0x05) {
    //     pixel_grb &= (0xffff00ff);  
    // }
    
    // if ((pixel_grb & 0x000000ff) < 0x05) {
    //     pixel_grb &= (0xffffff00);  
    // }
    pixel_grb = (g << 24) | (r << 16) | (b << 8);
    pio_sm_put_blocking(pio, sm, pixel_grb);
}







//make doom_tiny_usb_jumperless_v5

void jumperless_clearScreen(void) {

    for (int i = 0; i < NUM_PIXELS; ++i) {
        put_pixel(pio, sm, 0);
    }

}

void jumperless_initScreen(void) {



    stdio_init_all();


      tusb_init();


    printf("WS2812 Smoke Test, using pin %d\n", WS2812_PIN);

    // todo get free sm


    // This will find a free pio and state machine for our program and load it for us
    // We use pio_claim_free_sm_and_add_program_for_gpio_range (for_gpio_range variant)
    // so we will get a PIO instance suitable for addressing gpios >= 32 if needed and supported by the hardware
    // bool success2 = pio_claim_free_sm_and_add_program_for_gpio_range(&ws2812_program, &pio, &sm, &offset, WS2812_PIN, 1, true);
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&ws2812_program, &pio, &sm, &offset, WS2812_PIN, 1, true);
    hard_assert(success);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    int t = 0;
    // while (1) {
    //     int pat = 2;//rand() % count_of(pattern_table);
    //     int dir = (rand() >> 30) & 1 ? 1 : -1;
       // puts(pattern_table[2].name);
    //     puts(dir == 1 ? "(forward)" : "(backward)");
    //     for (int i = 0; i < 1000; ++i) {
    //         pattern_table[pat].pat(pio, sm, NUM_PIXELS, t);
    //         sleep_ms(10);
    //         t += dir;
    //     }
    // }

    // This will free resources and unload our program
    //pio_remove_program_and_unclaim_sm(&ws2812_program, pio, sm, offset);


}

void jumperless_handleFrameStart(uint8_t frame) {

}

void jumperless_blit(uint16_t* downsampled_line, int scanline) {

    // for (int i = 0; i < SCREENWIDTH; i++) {
    //     put_pixel(pio, sm, downsampled_line[i]);
    // }

    // this converts the line to "monochrome" greyscale
    // ditherDownsampledLine(downsampled_line);
    // for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
    //     uint16_t downsampled_pixel = downsampled_line[x];
        
    //     // comment out if using dithering
    //     downsampled_pixel = colorToGreyscale(downsampled_pixel);
        
    //     SSD1306_setPixel(buf,START_X + x, scanline, downsampled_pixel > 64);
    //     SSD1306_setPixel(second_buf,START_X + x, scanline, downsampled_pixel > 128);
    //     SSD1306_setPixel(third_buf,START_X + x, scanline, downsampled_pixel > 192);
    //     // SSD1306_render(buf, &screen_area);
    // }
}

uint16_t screen[NUM_PIXELS+100];
int dot = 0;


void jumperless_handleScanline(uint16_t *line, int scanline) {
   //nearestNeighborHandleDownsampling(line, scanline, ssd1306_70_40_i2c_blit);
   //nearestNeighborDownsampleLine(line, line);
    // for (int i = 0; i < SCREENWIDTH; i++) {
    //     put_pixel(pio, sm, line[i]);
    // }


    int downsample_w = 1;
    int downsample_h = 1;

    int offset_w = 0;//SCREENWIDTH / downsample_w;
    int offset_h = 0;//SCREENHEIGHT / downsample_h;

   for (int i = 0; i < LCD_WIDTH; i++) {
    int downscanline = scanline/downsample_h;
    if (downscanline < 5) {

        screen[(i*5)+downscanline] = line[(i*downsample_w)+offset_w];
        // if ((i*5)+scanline == dot) {
        //     screen[(i*5)+scanline] = 0xffff;
        //     dot++;
        // }
    } else if (downscanline < 10) {
        screen[(((i+29)*5)+(downscanline))] = line[(i*downsample_w)+offset_w];
        // if ((((i+29)*5)+scanline) == dot) {
        //     screen[(((i+29)*5)+scanline)] = 0xffff;
        //     dot++;
        // }
    } else {

        //screen[(((i+29)*5)+(downscanline))] = line[(i*downsample_w)+offset_w];


    }
    }

    // if (dot > 300) {
    //     dot = 0;
    // }


}

// TODO there's definitely a better way to do this
// with a separate "render" thread we could continue to oscillate between each frame while Doom renders the next
// this allows for better persistence of vision without biasing towards any particular frame
// but would also require a rewrite of the multithreading
void jumperless_handleFrameEnd(uint8_t frame) {
//jumperless_clearScreen();

    for (int i = 0; i < (NUM_PIXELS+60); i++) {

        // if (i >= 150 && i < 210) {
        //     continue;
        // }
        put_pixel(pio, sm, screen[i]);
        if (i > 300 && i < 400) {
            pio_sm_put_blocking(pio, sm, 0x00030303);
        }
        if (i > 400 && i < 500) {
            pio_sm_put_blocking(pio, sm, i*32);
        }
    }

    // for (int i = 300; i < NUM_PIXELS; i++) {
    //     put_pixel(pio, sm, 0x05050505);
    // }

    //sleep_ms(100);
    // for (int i = 0; i < SCREENWIDTH; i++) {
    //     put_pixel(pio, sm, line[i]);
    // }
    
    // park screen 
    // SSD1306_send_cmd_list(command_park,count_of(command_park));

    // // render first buffer
    // SSD1306_render(buf, &screen_area);

    // // unpark
    // SSD1306_send_cmd_list(command_run,count_of(command_run));

    // // use dead reckoning to try and get the screen to render once and only once, to avoid tearing
    // sleep_us(4000);

    // // park screen 
    // SSD1306_send_cmd_list(command_park,count_of(command_park));

    // // render second buffer
    // SSD1306_render(second_buf, &screen_area);

    // // unpark
    // SSD1306_send_cmd_list(command_run,count_of(command_run));

    // // use dead reckoning to try and get the screen to render once and only once, to avoid tearing
    // sleep_us(4000);

    // // park screen 
    // SSD1306_send_cmd_list(command_park,count_of(command_park));

    // // render third buffer
    // SSD1306_render(third_buf, &screen_area);

    // // unpark
    // SSD1306_send_cmd_list(command_run,count_of(command_run));

    // // use dead reckoning to try and get the screen to render once and only once, to avoid tearing
    // sleep_us(4000);


    // // park _again_, because  we don't know how long it'll take to render the next frame to Doom's framebuffer
    // // and if we don't know, we can't avoid frame tearing
    // SSD1306_send_cmd_list(command_park,count_of(command_park));

    // SSD1306_send_cmd(SSD1306_SET_NORM_DISP);
}





static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

static inline uint32_t urgbw_u32(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            ((uint32_t) (w) << 24) |
            (uint32_t) (b);
}


void pattern_snakes(PIO pio, uint sm, uint len, uint t) {
    for (uint i = 0; i < len; ++i) {
        uint x = (i + (t >> 1)) % 64;
        if (x < 10)
            put_pixel(pio, sm, urgb_u32(0xff, 0, 0));
        else if (x >= 15 && x < 25)
            put_pixel(pio, sm, urgb_u32(0, 0xff, 0));
        else if (x >= 30 && x < 40)
            put_pixel(pio, sm, urgb_u32(0, 0, 0xff));
        else
            put_pixel(pio, sm, 0);
    }
}

void pattern_random(PIO pio, uint sm, uint len, uint t) {
    if (t % 8)
        return;
    for (uint i = 0; i < len; ++i)
        put_pixel(pio, sm, rand());
}

void pattern_sparkle(PIO pio, uint sm, uint len, uint t) {
    if (t % 8)
        return;
    for (uint i = 0; i < len; ++i)
        put_pixel(pio, sm, rand() % 16 ? 0 : 0xffffffff);
}

void pattern_greys(PIO pio, uint sm, uint len, uint t) {
    uint max = 100; // let's not draw too much current!
    t %= max;
    for (uint i = 0; i < len; ++i) {
        put_pixel(pio, sm, t * 0x10101);
        if (++t >= max) t = 0;
    }
}

typedef void (*pattern)(PIO pio, uint sm, uint len, uint t);
const struct {
    pattern pat;
    const char *name;
} pattern_table[] = {
        {pattern_snakes,  "Snakes!"},
        {pattern_random,  "Random data"},
        {pattern_sparkle, "Sparkles"},
        {pattern_greys,   "Greys"},
};

