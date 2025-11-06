
#ifndef STRING_ART_H
#define STRING_ART_H

#include "simple_image.h"

#define BRIGHTEN_FIXED 0
#define BRIGHTEN_PERCENT 1
#define BRIGHTEN_AMOUNT 0.3
#define BRIGHTNESS_METHOD BRIGHTEN_PERCENT

double line_contrast(const image_t *img, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void brighten_line(const image_t *img, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);

#endif // STRING_ART_H
