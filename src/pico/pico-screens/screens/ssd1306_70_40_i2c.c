#include "ssd1306_70_40_i2c.h"
#include "pico/ssd1306_i2c.h"
#include "shared.h"



    // .spi      = PICO_DEFAULT_SPI_INSTANCE,
    // .gpio_din = PICO_DEFAULT_SPI_TX_PIN,
    // .gpio_clk = PICO_DEFAULT_SPI_SCK_PIN,
    // .gpio_cs  = PICO_DEFAULT_SPI_CSN_PIN,
    // .gpio_dc  = 20,
    // .gpio_rst = 21,
    // .gpio_bl  = 22,
// #define START_Y 24

// +4 to center on _72_ pixel width screen
// I counted, it's 72!
#define START_X (4)

static uint8_t buf[SSD1306_BUF_LEN+1];
// for greyscale
static uint8_t second_buf[SSD1306_BUF_LEN+1];
static uint8_t third_buf[SSD1306_BUF_LEN+1];

static uint8_t command_park[] = {
    0xA8, 1, //set minimum multiplex
    0xD3, 4, // set display offset off the top
};

static uint8_t command_run[] = {
    0xD3, 0,                // reset display offset
    0xA8, SSD1306_HEIGHT + 12 - 1,      // multiplex + overscan
};

static struct render_area screen_area = {
    start_col: SSD1306_70_40_START_COLUMN,
    end_col : SSD1306_70_40_END_COLUMN,
    start_page : SSD1306_70_40_START_PAGE,
    end_page : SSD1306_70_40_END_PAGE
};

// TODO move this to the screen library
void ssd1306_70_40_i2c_clearScreen(void) {
    memset(buf, 0, SSD1306_BUF_LEN);
    memset(second_buf, 0, SSD1306_BUF_LEN);
    memset(third_buf, 0, SSD1306_BUF_LEN);
}

void ssd1306_70_40_i2c_initScreen(void) {

    bi_decl(bi_2pins_with_func(22, 23, GPIO_FUNC_I2C));
    bi_decl(bi_program_description("SSD1306 OLED driver I2C example for the Raspberry Pi Pico"));
    // I2C is "open drain", pull ups to keep signal high when no data is being
    // sent
    i2c_init(i2c1, SSD1306_I2C_CLK * 1000);
    gpio_set_function(22, GPIO_FUNC_I2C);
    gpio_set_function(23, GPIO_FUNC_I2C);
    gpio_pull_up(22);
    gpio_pull_up(23);

    // run through the complete initialization process
    SSD1306_init();

    calc_render_area_buflen(&screen_area);
    ssd1306_70_40_i2c_clearScreen();
    SSD1306_render(buf, &screen_area);

    // SSD1306_send_cmd(SSD1306_SET_ALL_OFF);    // Set all pixels on
}

void ssd1306_70_40_i2c_handleFrameStart(uint8_t frame) {
    nearestNeighborHandleFrameStart();
    ssd1306_70_40_i2c_clearScreen();
}

void ssd1306_70_40_i2c_blit(uint16_t* downsampled_line, int scanline) {
    // this converts the line to "monochrome" greyscale
    // ditherDownsampledLine(downsampled_line);
    for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
        uint16_t downsampled_pixel = downsampled_line[x];
        
        // comment out if using dithering
        downsampled_pixel = colorToGreyscale(downsampled_pixel);
        
        SSD1306_setPixel(buf,START_X + x, scanline, downsampled_pixel > 64);
        SSD1306_setPixel(second_buf,START_X + x, scanline, downsampled_pixel > 128);
        SSD1306_setPixel(third_buf,START_X + x, scanline, downsampled_pixel > 192);
        // SSD1306_render(buf, &screen_area);
    }
}


void ssd1306_70_40_i2c_handleScanline(uint16_t *line, int scanline) {
    nearestNeighborHandleDownsampling(line, scanline, ssd1306_70_40_i2c_blit);
}

// TODO there's definitely a better way to do this
// with a separate "render" thread we could continue to oscillate between each frame while Doom renders the next
// this allows for better persistence of vision without biasing towards any particular frame
// but would also require a rewrite of the multithreading
void ssd1306_70_40_i2c_handleFrameEnd(uint8_t frame) {
    // park screen 
    SSD1306_send_cmd_list(command_park,count_of(command_park));

    // render first buffer
    SSD1306_render(buf, &screen_area);

    // unpark
    SSD1306_send_cmd_list(command_run,count_of(command_run));

    // use dead reckoning to try and get the screen to render once and only once, to avoid tearing
    sleep_us(4000);

    // park screen 
    SSD1306_send_cmd_list(command_park,count_of(command_park));

    // render second buffer
    SSD1306_render(second_buf, &screen_area);

    // unpark
    SSD1306_send_cmd_list(command_run,count_of(command_run));

    // use dead reckoning to try and get the screen to render once and only once, to avoid tearing
    sleep_us(4000);

    // park screen 
    SSD1306_send_cmd_list(command_park,count_of(command_park));

    // render third buffer
    SSD1306_render(third_buf, &screen_area);

    // unpark
    SSD1306_send_cmd_list(command_run,count_of(command_run));

    // use dead reckoning to try and get the screen to render once and only once, to avoid tearing
    sleep_us(4000);


    // park _again_, because  we don't know how long it'll take to render the next frame to Doom's framebuffer
    // and if we don't know, we can't avoid frame tearing
    SSD1306_send_cmd_list(command_park,count_of(command_park));

    // SSD1306_send_cmd(SSD1306_SET_NORM_DISP);
}