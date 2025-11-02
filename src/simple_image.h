
#ifndef SIMPLE_IMAGE_H
#define SIMPLE_IMAGE_H

#include <stdint.h>
// #define NDEBUG
#include <assert.h>

// Force RGB
#define DESIRED_CHANNELS 3
#define JPG_QUALITY 100

#define RED 0
#define GREEN 1
#define BLUE 2

// RGB -> GRAY
#define WEIGHTED_AVERAGE 0
#define SIMPLE_AVERAGE 1
#define LUMINOSITY 2
#define GRAYSCALE_METHOD WEIGHTED_AVERAGE

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
image_t generate_rgb_image(uint32_t width, uint32_t height);
image_t generate_y_image(uint32_t width, uint32_t height);
image_t to_gray(image_t *color);
void clear_image(image_t *img, pixel_t p);
void draw_line(image_t *img, int x0, int y0, int x1, int y1, pixel_t p);
void save_image(const image_t* img, const char* filename);
void write_pixel(image_t *img, uint32_t x, uint32_t y, pixel_t p);
pixel_t pixel_at(const image_t* img, uint32_t x, uint32_t y);
void show_pixel(const pixel_t* p);
void free_image(image_t *img);

#endif // SIMPLE_IMAGE_H
