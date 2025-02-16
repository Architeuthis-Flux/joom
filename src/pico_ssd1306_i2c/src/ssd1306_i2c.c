/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "pico/ssd1306_i2c.h"

void SSD1306_send_cmd(uint8_t cmd) {
    // I2C write process expects a control byte followed by data
    // this "data" can be a command or data to follow up a command
    // Co = 1, D/C = 0 => the driver expects a command
    uint8_t buf[2] = {0x80, cmd};
    i2c_write_blocking(i2c1, (SSD1306_I2C_ADDR & SSD1306_WRITE_MODE), buf, 2, false);
}

void SSD1306_send_cmd_list(uint8_t *buf, int num) {
    for (int i=0;i<num;i++)
        SSD1306_send_cmd(buf[i]);
}

// color is 8 bits
void SSD1306_send_color(int len, int color) {
    uint8_t *temp_buf = malloc(len + 1);
    temp_buf[0] = 0x40;
    for (uint16_t i = 1; i <= len; i++) {
        temp_buf[i] = color;
    }

   
    i2c_write_blocking(i2c1, (SSD1306_I2C_ADDR & SSD1306_WRITE_MODE), temp_buf, len + 1, false);

    free(temp_buf); 
}


void SSD1306_send_buf(uint8_t buf[], int buflen) {
    // in horizontal addressing mode, the column address pointer auto-increments
    // and then wraps around to the next page, so we can send the entire frame
    // buffer in one gooooooo!

    // copy our frame buffer into a new buffer because we need to add the control byte
    // to the beginning

    // uint8_t *temp_buf = malloc(1);

    // make way for control bit.
    for (uint16_t i = buflen; i > 1; i--) {
        buf[i] = buf[i-1];
    }
    buf[0] = 0x40;
    // memcpy(temp_buf+1, buf, buflen);

    // i2c_write_blocking(i2c1, (SSD1306_I2C_ADDR & SSD1306_WRITE_MODE), temp_buf, 1, false);
    i2c_write_blocking(i2c1, (SSD1306_I2C_ADDR & SSD1306_WRITE_MODE), buf, buflen+1, false);

    // free(temp_buf);
}

void SSD1306_init() {
    // Some of these commands are not strictly necessary as the reset
    // process defaults to some of these but they are shown here
    // to demonstrate what the initialization sequence looks like
    // Some configuration values are recommended by the board manufacturer

//     uint8_t cmds[] = {
//         SSD1306_SET_DISP,               // set display off
//         /* memory mapping */
//         SSD1306_SET_MEM_MODE,           // set memory address mode 0 = horizontal, 1 = vertical, 2 = page
//         0x00,                           // horizontal addressing mode
//         /* resolution and layout */
//         SSD1306_SET_DISP_START_LINE,    // set display start line to 0
//         SSD1306_SET_SEG_REMAP | 0x01,   // set segment re-map, column address 127 is mapped to SEG0
//         SSD1306_SET_MUX_RATIO,          // set multiplex ratio
//         SSD1306_HEIGHT - 1,             // Display height - 1
//         SSD1306_SET_COM_OUT_DIR | 0x08, // set COM (common) output scan direction. Scan from bottom up, COM[N-1] to COM0
//         SSD1306_SET_DISP_OFFSET,        // set display offset
//         0x00,                           // no offset
//         SSD1306_SET_COM_PIN_CFG,        // set COM (common) pins hardware configuration. Board specific magic number. 
//                                         // 0x02 Works for 128x32, 0x12 Possibly works for 128x64. Other options 0x22, 0x32
// #if ((SSD1306_WIDTH == 128) && (SSD1306_HEIGHT == 32))
//         0x02,                           
// #elif ((SSD1306_WIDTH == 128) && (SSD1306_HEIGHT == 64))
//         0x12,
// #else
//         0x02,
// #endif
//         /* timing and driving scheme */
//         SSD1306_SET_DISP_CLK_DIV,       // set display clock divide ratio
//         0x80,                           // div ratio of 1, standard freq
//         SSD1306_SET_PRECHARGE,          // set pre-charge period
//         0xF1,                           // Vcc internally generated on our board
//         SSD1306_SET_VCOM_DESEL,         // set VCOMH deselect level
//         0x30,                           // 0.83xVcc
//         /* display */
//         SSD1306_SET_CONTRAST,           // set contrast control
//         0xFF,
//         SSD1306_SET_ENTIRE_ON,          // set entire display on to follow RAM content
//         SSD1306_SET_NORM_DISP,           // set normal (not inverted) display
//         SSD1306_SET_CHARGE_PUMP,        // set charge pump
//         0x14,                           // Vcc internally generated on our board
//         SSD1306_SET_SCROLL | 0x00,      // deactivate horizontal scrolling if set. This is necessary as memory writes will corrupt if scrolling was enabled
//         SSD1306_SET_DISP | 0x01, // turn display on
//     };

    // from ugrey
    uint8_t commands[] = {
        0xAE,           // display off
        0xD5, 0xF0,     // set display clock divide
        0xA8, 39,       // set multiplex ratio 39
        0xD3, 0x00,     // set display offset
        0x40,           // set display start line 0
        0x8D, 0x14,     // set charge pump enabled (0x14:7.5v 0x15:6.0v 0x94:8.5v 0x95:9.0v)
        0x20, 0x00,     // set addressing mode horizontal
        0xA0,           // set segment remap (0=seg0)
        // SSD1306_SET_SEG_REMAP | 0x01,   // set segment re-map, column address 127 is mapped to SEG0
        0xC0,           // set com scan direction
        0xDA, 0x12,     // set alternate com pin configuration
        0xAD, 0x30,     // internal iref enabled (0x30:240uA 0x10:150uA)
        0x81, 0x01,     // set display_contrast
        0xD9, 0x11,     // set pre-charge period
        0xDB, 0x20,     // set vcomh deselect
        0xA4,           // unset entire display on
        0xA6,           // unset inverse display
        // 0x21, 28, 99,   // set column address / start 28 / end 99
        0x21, 28, 36,   // set column address / start 28 / end 99
        0x22, 0, 4,     // set page address / start 0 / end 4
        0x81, 1,                //set contrast
        0xAF            //  set display on
    };

    SSD1306_send_cmd_list(commands, count_of(commands));
}

void calc_render_area_buflen(struct render_area *area) {
    // calculate how long the flattened buffer will be for a render area
    area->buflen = (area->end_col - area->start_col + 1) * (area->end_page - area->start_page + 1);
}

void SSD1306_begin_render(void) {
    // update a portion of the display with a render area
    uint8_t cmds[] = {
        SSD1306_SET_COL_ADDR,
        SSD1306_70_40_START_COLUMN,
        SSD1306_70_40_END_COLUMN,
        SSD1306_SET_PAGE_ADDR,
        SSD1306_70_40_START_PAGE,
        SSD1306_70_40_END_PAGE
    };
    
    SSD1306_send_cmd_list(cmds, count_of(cmds));
}

void SSD1306_render(uint8_t *buf, struct render_area *area) {
    SSD1306_begin_render();
    SSD1306_send_buf(buf, area->buflen);
}

// TODO can't do this, can't handle malloc'ing that much memory
void SSD1306_clear(uint8_t *buf) {
    memset(buf, 0, SSD1306_BUF_LEN);

    // // update a portion of the display with a render area
    // uint8_t cmds[] = {
    //     SSD1306_SET_COL_ADDR,
    //     0,
    //     SSD1306_MEMORY_WIDTH-1,
    //     SSD1306_SET_PAGE_ADDR,
    //     0,
    //     SSD1306_NUM_MEMORY_PAGE_ROWS - 1
    // };
    
    // SSD1306_send_cmd_list(cmds, count_of(cmds));
    // SSD1306_send_color(SSD1306_MEMORY_WIDTH * SSD1306_MEMORY_HEIGHT / SSD1306_PAGE_HEIGHT, 0); // TODO constant for memory width
    // SSD1306_render(buf, )
}

void SSD1306_render_color(int len, int color) {
    // update a portion of the display with a render area
    // uint8_t cmds[] = {
    //     0x21, 28, 98+1,   // set column address / start 28 / end 99
    //     0x22, 0, 4,     // set page address / start 0 / end 4
    // };
    
    // SSD1306_send_cmd_list(cmds, count_of(cmds));
    SSD1306_begin_render();
    SSD1306_send_color(len, color);
}

void SSD1306_setPixel(uint8_t *buf, int x,int y, bool on) {
    assert(x >= 0 && x < SSD1306_WIDTH && y >=0 && y < SSD1306_HEIGHT);

    // The calculation to determine the correct bit to set depends on which address
    // mode we are in. This code assumes horizontal

    // The video ram on the SSD1306 is split up in to 8 rows, one bit per pixel.
    // Each row is 128 long by 8 pixels high, each byte vertically arranged, so byte 0 is x=0, y=0->7,
    // byte 1 is x = 1, y=0->7 etc

    // This code could be optimised, but is like this for clarity. The compiler
    // should do a half decent job optimising it anyway.

    const int BytesPerRow = SSD1306_WIDTH ; // x pixels, 1bpp, but each row is 8 pixel high, so (x / 8) * 8

    int byte_idx = (y / 8) * BytesPerRow + x;
    uint8_t byte = buf[byte_idx]; // we add 1 to every placement, effectively making this buffer 1-indexed, because we need buf[0] to be the control bit

    if (on)
        byte |=  1 << (y % 8);
    else
        byte &= ~(1 << (y % 8));

    buf[byte_idx] = byte;
}
