
#ifndef STRING_ART_H
#define STRING_ART_H

#include <stdint.h>
// #define NDEBUG
#include <assert.h>

// Force RGB
#define DESIRED_CHANNELS 3
#define JPG_QUALITY 100

#define RED 0
#define GREEN 1
#define BLUE 2

typedef struct {
    int width;
    int height;
    int channels;
    unsigned char *data;
} image_t;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pixel_t;

image_t load_image(const char* filename);
image_t generate_image(uint32_t width, uint32_t height);
void clear_image(image_t *img, pixel_t p);
void draw_line(image_t *img, uint32_t x0, uint32_t y0,
        uint32_t x1, uint32_t y1, pixel_t p);
void save_image(const image_t* img, const char* filename);
void write_pixel(image_t *img, uint32_t x, uint32_t y, pixel_t p);
pixel_t pixel_at(const image_t* img, uint32_t x, uint32_t y);
void show_pixel(const pixel_t* p);
void free_image(image_t *img);

#endif // STRING_ART_H
