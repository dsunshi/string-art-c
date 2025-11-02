
#include <stdio.h>
#include <stdint.h>
// #define NDEBUG
#include <assert.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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

image_t load_image(const char* filename) {
    image_t result;

    result.data = stbi_load(filename, &result.width, &result.height, &result.channels, DESIRED_CHANNELS);

    if (result.data == NULL) {
        printf("[ERROR] loading %s: %s\n", filename, stbi_failure_reason());
        result.width    = 0;
        result.height   = 0;
        result.channels = 0;
    }

    return result;
}

void save_image(const image_t* img, const char* filename) {
    stbi_write_jpg(filename, img->width, img->height, DESIRED_CHANNELS, img->data, JPG_QUALITY);
}

pixel_t pixel_at(const image_t* img, uint32_t x, uint32_t y) {
    pixel_t p;
    
    assert(img != NULL);
    assert(img->data != NULL);

    // The pixel data consists of *y scanlines of *x pixels,
    // with each pixel consisting of N interleaved 8-bit components
    uint32_t i = img->channels * (img->width * y + x);

    p.r = img->data[i + RED];
    p.g = img->data[i + GREEN];
    p.b = img->data[i + BLUE];

    return p;
}

void show_pixel(const pixel_t* p) {
    printf("%02X%02X%02X\n", p->r, p->g, p->b);
}

int main (void) {
    char *input  = "PixelTest.jpg";
    char *output = "Result.jpg";

    image_t img = load_image(input);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            pixel_t p = pixel_at(&img, x, y);
            show_pixel(&p);
        }
    }

    save_image(&img, output);

    stbi_image_free(img.data);

    return 0;
}
