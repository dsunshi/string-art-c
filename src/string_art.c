
#include "string_art.h"
#include <stdlib.h>
#include <math.h>

float line_contrast(const image_t *img, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;
    float sum = 0;
    float len = sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));

    while (true) {
        const uint32_t i = img->channels * (img->width * y0 + x0);
        sum += img->data[i];
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

