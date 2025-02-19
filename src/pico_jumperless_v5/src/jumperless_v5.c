#include "pico/pico-screens/screens/jumperless_v5.h"
#include "pico/pico-screens/screens/shared.h"
#include "pico_jumperless_matrix.h"
#include "pico-screens/screens/shared.h"
#include "ws2812.pio.h"

#include "hardware/pio.h"
#include "hardware/clocks.h"

#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h" 
// #include "pico/usb_device.h"
//#include "tusb.h"
// #include "board_api.h"
//#include "shared.h"
#define IS_RGBW false
#define WS2812_PIN 17
#define NUM_PIXELS 445

#include "d_main.h"

// #define WS2812_PIN_1 17
// #define NUM_PIXELS_1 300

// #define WS2812_PIN_2 3
// #define NUM_PIXELS_2 145


void jumperless_clearScreen(void);



PIO pio;
uint sm;
uint offset;

// Check the pin is compatible with the platform
#if WS2812_PIN >= NUM_BANK0_GPIOS
#error Attempting to use a pin>=32 on a platform that does not support it
#endif

static inline void put_pixel(PIO pio, uint sm, uint16_t pixel, int dim) {

    //pixel_grb &= 0x002f1f1f;
    // pixel_grb <<= 8u;
    uint8_t r = (pixel & 0b1111100000000000) >> 11;
    uint8_t g = (pixel & 0b0000011111100000) >> 6;
    uint8_t b = (pixel & 0b0000000000011111) << 0;

    // uint8_t r = ((downsampled_pixel & 0b1111100000000000) >> 11) ;
    // uint8_t g = ((downsampled_pixel & 0b0000011111100000) >> 5) ;
    // uint8_t b = ( downsampled_pixel & 0b0000000000011111);

    uint32_t averaged_pixel;
    // averaged_pixel  =   (b)        & 0b0000000000011111;
    // averaged_pixel |= (((g) << 5)  & 0b0000011111100000);
    // averaged_pixel |= (((r) << 11) & 0b1111100000000000);


    if (dim == 1) {
        r = r >> 1;
        g = g >> 1;
        b = b >>   1;
    }
        //  if (r < 0x05 && r > 0) {
        //     r -= 0x01;
        // }
        // if (g < 0x05 && g > 0) {
        //     g -= 0x01;
        // }
        // if (b < 0x05 && b > 0) {
        //     b -= 0x01;
        //  }

         r = r*r;
         g = g*g;   
        b = b*b;
        
        // r = r >> 1;
        // g = g >> 1;
        // b = b >> 1;
if (dim == 1) {
        if (r + g + b < 0x0c) {
            if (r < 0x0a && b < 0x0a && g < 0x0a) {

            
            r = 0;
            g = 0;
            b = 0;
            }
        }
    }

   // }
    averaged_pixel = b << 8;
    averaged_pixel |= r << 16;
    averaged_pixel |= g << 24;
    // averaged_pixel = b << 10;
    // averaged_pixel |= r << 18;
    // averaged_pixel |= g << 26;

   // averaged_pixel = averaged_pixel << 8;
    
   // r=0;
    //g=0;
    //b=0;

    //pixel 0b rrrrr0 gggggg bbbbb0

    //pixel_grb 0b ggggggxx rrrrrgxx bbbbbgxx 00000000 



    if (dim == 1) {

        }

     pixel = ((g << 11) | (r << 5) | (b << 0));
//pixel = pixel << 16;
    pio_sm_put_blocking(pio, sm, averaged_pixel);
    }


void jumperless_initScreen(void) {


    //board_init();


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
    //stdio_init_all();

    //stdio_usb_init();
    //tusb_init();
    // tud_init();

//tud_task();
 // while (!tud_cdc_connected()) {
 //     sleep_ms(100);
 //     }
    uint32_t led = 1;

    // for (int i = 0; i < 100; i++) {
        //put_pixel(pio, sm, 0x000a0a0a);
        // if (i == led) {
        //     put_pixel(pio, sm, 0x0000ff00);
        //     led++;
        // }


// led = i*16;
        // for (int j = 0; j < 30; j++) {
        //     put_pixel(pio, sm, (led<<(j%8)&0x0f0f0f0f), 0);
        //     tud_task();
        //     led++;
        //     }
        // tud_task();
        //printf("WS2812 Smoke Test, using pin %d\n", WS2812_PIN);
       // sleep_us(3000);

       // put_pixel(pio, sm, 0x000a000a);
        // }
        // jumperless_clearScreen();
    // This will free resources and unload our program
    //pio_remove_program_and_unclaim_sm(&ws2812_program, pio, sm, offset);


    }

void jumperless_handleFrameStart(uint8_t frame) {

    }


    uint16_t screen[NUM_PIXELS + 100];
int dot = 0;

int scanlineOrder[20] = { 99, 10, 11,  0, 1, 2, 3, 4, 5, 6, 7, 8 , 9, 99,  12, 13,99,99, 99, 99, };

void jumperless_blit(uint16_t* downsampled_line, int scanline) {

 
    }


void jumperless_handleScanline(uint16_t* line, int scanline) {
  

    int downsample_w = 10;
    int downsample_h = 13;



    int offset_w = 10;//SCREENWIDTH / downsample_w;
    
    
    int offset_h = 0;//SCREENHEIGHT / downsample_h;



        offset_h = 0;
        downsample_h = 10;
    

    for (int i = 0; i < LCD_WIDTH; i++) {

        int downscanline = ((scanline + offset_h)/ downsample_h)+1;
        if (downscanline < 0) {
            continue;
        }

        if (scanlineOrder[downscanline] == 99) {
            continue;
            
        }

        if (scanlineOrder[downscanline] >=14) {
            return;
            
        }
        if (scanlineOrder[downscanline] < 5) {

            screen[(i * 5) + scanlineOrder[downscanline]] = line[(i * downsample_w) + offset_w];
            // if ((i*5)+scanline == dot) {
            //     screen[(i*5)+scanline] = 0xffff;
            //     dot++;
            // }
        } else if (scanlineOrder[downscanline] < 10) {
                screen[(((i + 29) * 5) + scanlineOrder[downscanline])] = line[(i * downsample_w) + offset_w];
                // if ((((i+29)*5)+scanline) == dot) {
                //     screen[(((i+29)*5)+scanline)] = 0xffff;
                //     dot++;
                // }
        } else if (scanlineOrder[downscanline] < 14) {

                    if (i < 25){
                    screen[(300 + ((scanlineOrder[downscanline] - 10)*25) + i)] = line[(i * downsample_w) - (downsample_w/2) + offset_w];
                    }
                    //screen[(((i+29)*5)+(downscanline))] = line[(i*downsample_w)+offset_w];


                    }
        }

    // if (dot > 300) {
    //     dot = 0;
    // }


    }

    uint16_t rainbowr[30] = { 30, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 30 };
    uint16_t rainbowg[30] = {  0,  2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 30, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2, 0, 0, 0, 0, 0, 0, 2, 5 };
    uint16_t rainbowb[30] = {  0,  0, 0, 0, 0, 0, 0, 0, 2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 30, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2 };


// with a separate "render" thread we could continue to oscillate between each frame while Doom renders the next
// this allows for better persistence of vision without biasing towards any particular frame
// but would also require a rewrite of the multithreading
int framecountforusb = 0;
int cycleCounter = 0;
void jumperless_handleFrameEnd(uint8_t frame) {
    //jumperless_clearScreen();
//tud_task();

    framecountforusb++;

    if (framecountforusb > 4) {
        cycleCounter++;
        framecountforusb = 0;
        //tud_task();
    }

     if (cycleCounter > 29) {
        cycleCounter = 0;
        //tud_task();
    }


    for (int i = 0; i < (NUM_PIXELS); i++) {

        // if (i >= 150 && i < 210) {
        //     continue;
        // }
        if (i < 400) {
            put_pixel(pio, sm, screen[i], 1);
            }
      //  put_pixel(pio, sm, screen[i], 1);
        // if (i > 300 && i < 400) {
        //     pio_sm_put_blocking(pio, sm, 0x00030303);
        //     }
         else if (i >= 400 && i < 446) {
            uint8_t pixel_r = 3;
            uint8_t pixel_g = 0;
            uint8_t pixel_b = 1;
            // switch (((i-400)+(framecountforusb/8))%3) {
            //     case 0:
            //         pixel_r = ((framecountforusb/8)%255);
            //         pixel_g = ((framecountforusb/8)%128);
            //         pixel_b = 0;//(i%64);
            //        // put_pixel(pio, sm, pixel_r, 1);
            //         break;
            //     case 1:
            //         pixel_b = ((framecountforusb/8)%255);
            //         pixel_r = ((framecountforusb/8)%128);
            //         pixel_g = 0;//(i%64);
            //         //put_pixel(pio, sm, pixel_g, 1);
            //         break;
            //     case 2:
            //         pixel_g = ((framecountforusb/8)%255);
            //         pixel_b = ((framecountforusb/8)%128);
            //         pixel_r = 0;//(i%64);
            //         //put_pixel(pio, sm, pixel_b, 1);
            //         break;
            //     }

            if (i > 429) {
                int index = (i-400);
                pixel_r = rainbowr[(cycleCounter+index)%30]/4;
                pixel_g = rainbowg[(cycleCounter+index)%30]/4;
                pixel_b = rainbowb[(cycleCounter+index)%30]/4;
                } else {

                }
         
             


            uint16_t pixel = (pixel_r&0b00011111)<<11 | (pixel_g&0b00011111)<<6 | (pixel_b&0b00011111);


            put_pixel(pio, sm, pixel, 0);
           //pio_sm_put_blocking(pio, sm, i );
            }
        }
        //sleep_ms(2);
    //tud_task();
    //if (framecountforusb > 25) {
        //tud_task();
        //framecountforusb = 0;

    //}


    // if(tud_task_event_ready()){
    //     tud_task();
    // }
    }



void jumperless_clearScreen(void) {

    for (int i = 0; i < NUM_PIXELS; ++i) {
        put_pixel(pio, sm, 0, 0);
        }

    }

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
        ((uint32_t)(r) << 8) |
        ((uint32_t)(g) << 16) |
        (uint32_t)(b);
    }

static inline uint32_t urgbw_u32(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    return
        ((uint32_t)(r) << 8) |
        ((uint32_t)(g) << 16) |
        ((uint32_t)(w) << 24) |
        (uint32_t)(b);
    }


void pattern_snakes(PIO pio, uint sm, uint len, uint t) {
    for (uint i = 0; i < len; ++i) {
        uint x = (i + (t >> 1)) % 64;
        if (x < 10)
            put_pixel(pio, sm, urgb_u32(0xff, 0, 0), 0);
        else if (x >= 15 && x < 25)
            put_pixel(pio, sm, urgb_u32(0, 0xff, 0), 0);
        else if (x >= 30 && x < 40)
            put_pixel(pio, sm, urgb_u32(0, 0, 0xff), 0);
        else
            put_pixel(pio, sm, 0, 0);
        }
    }

void pattern_random(PIO pio, uint sm, uint len, uint t) {
    if (t % 8)
        return;
    for (uint i = 0; i < len; ++i)
        put_pixel(pio, sm, rand(), 0);
    }

void pattern_sparkle(PIO pio, uint sm, uint len, uint t) {
    if (t % 8)
        return;
    for (uint i = 0; i < len; ++i)
        put_pixel(pio, sm, rand() % 16 ? 0 : 0xffffffff, 0);
    }

void pattern_greys(PIO pio, uint sm, uint len, uint t) {
    uint max = 100; // let's not draw too much current!
    t %= max;
    for (uint i = 0; i < len; ++i) {
        put_pixel(pio, sm, t * 0x10101, 0);
        if (++t >= max) t = 0;
        }
    }

typedef void (*pattern)(PIO pio, uint sm, uint len, uint t);
const struct {
    pattern pat;
    const char* name;
    } pattern_table[] = {
            {pattern_snakes,  "Snakes!"},
            {pattern_random,  "Random data"},
            {pattern_sparkle, "Sparkles"},
            {pattern_greys,   "Greys"},
        };

