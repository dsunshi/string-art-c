
#include "string_art.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double line_contrast(const image_t *img, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
    int dx = abs((int)(x1) - (int)(x0));
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs((int)(y1) - (int)(y0));
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;

    double sum = 0;
    double lum = 0;
    double len = sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));

    while (true) {
        const uint32_t i = img->channels * (img->width * y0 + x0);
        // Adjust 0 (Black) to 255 (White) to
        // 0 (White) to 1.0 (Black)
        lum = CLAMP_PIXEL(img->data[i]);
        lum = lum / 255.0;
        lum = 1.0 - lum;
        sum += lum;

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

    return sum / len;
}


void brighten_line(const image_t *img, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
    int dx = abs((int)(x1) - (int)(x0));
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs((int)(y1) - (int)(y0));
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;
    double lum = 0;

    while (true) {
        const uint32_t i = img->channels * (img->width * y0 + x0);

        if (BRIGHTNESS_METHOD == BRIGHTEN_FIXED) {
            lum = img->data[i] + BRIGHTEN_AMOUNT;
        } else if (BRIGHTNESS_METHOD == BRIGHTEN_PERCENT) {
            lum = img->data[i] + (255 - img->data[i]) * BRIGHTEN_AMOUNT;
        } else {
            printf("[ERROR] Unknown brightness method: %d\n", BRIGHTNESS_METHOD);
        }

        img->data[i] = (unsigned char) CLAMP_PIXEL(lum);

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

