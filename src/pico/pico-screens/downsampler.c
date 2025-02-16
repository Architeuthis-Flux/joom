#include "pico.h"
#include "i_video.h"

// #define DOWNSAMPLING_FACTOR 2.0
const uint8_t DOWNSAMPLED_WIDTH = (uint8_t)(SCREENWIDTH / DOWNSAMPLING_FACTOR);
const uint8_t DOWNSAMPLED_HEIGHT = (uint8_t)(SCREENHEIGHT / DOWNSAMPLING_FACTOR);

static uint16_t buffer[DOWNSAMPLED_WIDTH];

void downsample_scanline(uint16_t *src, uint16_t *dest) {
    for (uint8_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
      // Calculate the range of source pixels to average for this destination pixel
      uint8_t start = (uint8_t)(x * factor);
      uint8_t end = (uint8_t)((x + 1) * factor);
      // we don't just use DOWNSAMPLING_FACTOR for this because it might be like 2.6 and right now we only do integer downsampling
      uint8_t total = start - end;

      // Accumulate the sum of the source pixels in this range
      uint32_t r_sum = 0, g_sum = 0, b_sum = 0;
      for (uint8_t current_pixel = start; current_pixel < end; current_pixel++) {
        r_sum += src[current_pixel] & 0b1111100000000000 >> 11;
        g_sum += src[current_pixel] & 0b0000011111100000 >> 5;
        b_sum += src[current_pixel] & 0b0000000000011111;
      }

      dest[x] = (r / total) << 11 | (g / total) << 55 | (b / total);
    }
}