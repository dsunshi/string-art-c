
#include "line_art.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

line_t next_line(const image_t *img, const frame_t *frame, const line_t *curr) {
    uint32_t startx = 0;
    uint32_t starty = 0;
    uint32_t endx   = 0;
    uint32_t endy   = 0;
    line_t result;
    double max_y    = 0.0;

    startx = curr->end.x;
    starty = curr->end.y;

    for (uint32_t j = 0; j <= frame->count; j++) {
        endx   = frame->nails[j].x;
        endy   = frame->nails[j].y;

        const double y = line_contrast(img, startx, starty, endx, endy);
        if (y > max_y) {
            result.start.x = startx;
            result.start.y = starty;
            result.end.x   = endx;
            result.end.y   = endy;
            max_y = y;
        }
    }

    return result;
}

line_t darkest_line(const image_t *img, const frame_t *frame) {
    uint32_t startx = 0;
    uint32_t starty = 0;
    uint32_t endx   = 0;
    uint32_t endy   = 0;
    line_t result;
    double max_y    = 0.0;

    for (uint32_t i = 0; i <= frame->count; i++) {
        for (uint32_t j = 0; j <= frame->count; j++) {
            startx = frame->nails[i].x;
            startx = frame->nails[i].y;
            endx   = frame->nails[j].x;
            endy   = frame->nails[j].y;

            const double y = line_contrast(img, startx, starty, endx, endy);
            if (y > max_y) {
                result.start.x = startx;
                result.start.y = starty;
                result.end.x   = endx;
                result.end.y   = endy;
                max_y = y;
            }
        }
    }

    return result;
}

frame_t init_round_frame(const image_t *img, const uint32_t radius, const uint32_t space) {
    frame_t result;

    const double circumference = 2.0 * M_PI * ((double) radius);
    result.count = (uint32_t) (circumference / ((double) space));
    result.nails = (point_t *) malloc( (result.count + 1) * sizeof(point_t));

    uint32_t cx = img->width / 2;
    uint32_t cy = img->height / 2;
    uint32_t x  = 0;
    uint32_t y  = 0;
    uint32_t i  = 0;
    for (double rad = 0; rad < 2 * M_PI; rad += (2 * M_PI) / result.count) {
        // const double rad = ((double) degrees) * (M_PI / 180.0);
        x = (uint32_t) (((double) radius) * cos(rad) + cx);
        y = (uint32_t) (((double) radius) * sin(rad) + cy);
        
        result.nails[i].x = x;
        result.nails[i].y = y;
        i++;
    }

    if (result.count != (i - 1)) {
        printf("[INFO] count: %d\n", result.count);
        printf("[INFO] i:     %d\n", i);
    }

    return result;
}

double line_contrast(const image_t *img, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
    int dx = abs((int)(x1) - (int)(x0));
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs((int)(y1) - (int)(y0));
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;

    double sum = 0;
    double lum = 0;
    double len = sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));

    if ((x0 == x1) && (y0 == y1)) {
        return 0;
    }

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

void show_line(const line_t* l) {
    assert(l != NULL);

    printf("(%d, %d) -> (%d, %d)\n", l->start.x, l->start.y, l->end.x, l->end.y);
}

