
#include "string_art.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

image_t load_image(const char* filename) {
    image_t result;

    result.data = stbi_load(filename,
            &result.width, &result.height, &result.channels, DESIRED_CHANNELS);

    if (result.data == NULL) {
        printf("[ERROR] loading %s: %s\n", filename, stbi_failure_reason());
        result.width    = 0;
        result.height   = 0;
        result.channels = 0;
    }

    return result;
}

void free_image(image_t *img) {
    stbi_image_free(img->data);
}

image_t generate_image(uint32_t width, uint32_t height) {
    image_t result;

    result.width    = width;
    result.height   = height;
    result.channels = DESIRED_CHANNELS;
    result.data     = (unsigned char *) malloc((width * height * DESIRED_CHANNELS) * sizeof(unsigned char));

    return result;
}

void clear_image(image_t *img, pixel_t p) {
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            const uint32_t i = img->channels * (img->width * y + x);

            img->data[i + RED]   = p.r;
            img->data[i + GREEN] = p.g;
            img->data[i + BLUE]  = p.b;
        }
    }
}

void draw_line(image_t *img, int x0, int y0, int x1, int y1, pixel_t p) {
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;

    while (1) {
        write_pixel(img, x0, y0, p);
        int e2 = 2 * error;
        if (e2 >= dy) {
            if (x0 == x1) break;
            error = error + dy;
            x0 = x0 + sx;
        }
        if (e2 <= dx) {
            if (y0 == y1) break;
            error = error + dx;
            y0 = y0 + sy;
        }
    }
}


void save_image(const image_t* img, const char* filename) {
    const int err = stbi_write_jpg(filename,
            img->width, img->height, DESIRED_CHANNELS, img->data, JPG_QUALITY);
    if (err != 0 ) {
        printf("[WARNING] saving %s: %s\n", filename, stbi_failure_reason());
    }
}


void write_pixel(image_t *img, uint32_t x, uint32_t y, pixel_t p) {
    assert(img != NULL);
    assert(img->data != NULL);

    const uint32_t i = img->channels * (img->width * y + x);

    img->data[i + RED]   = p.r;
    img->data[i + GREEN] = p.g;
    img->data[i + BLUE]  = p.b;
}

pixel_t pixel_at(const image_t* img, uint32_t x, uint32_t y) {
    pixel_t p;
    
    assert(img != NULL);
    assert(img->data != NULL);

    // The pixel data consists of `y` scanlines of `x` pixels,
    // with each pixel consisting of DESIRED_CHANNELS interleaved 8-bit components
    const uint32_t i = img->channels * (img->width * y + x);

    p.r = img->data[i + RED];
    p.g = img->data[i + GREEN];
    p.b = img->data[i + BLUE];

    return p;
}

void show_pixel(const pixel_t* p) {
    assert(p != NULL);

    printf("%02X%02X%02X\n", p->r, p->g, p->b);
}
