
#ifndef LINE_ART_H
#define LINE_ART_H

#include "config.h"
#include "simple_image.h"

typedef struct {
    uint32_t x;
    uint32_t y;
} point_t;

typedef struct {
    point_t start;
    point_t end;
} line_t;

typedef struct {
    point_t *nails;
    uint32_t count;
} frame_t;

double line_contrast(const image_t *img, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void brighten_line(const image_t *img, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
frame_t init_round_frame(const image_t *img, const uint32_t radius, const uint32_t space);
line_t darkest_line(const image_t *img, const frame_t *frame);
void show_line(const line_t* l);

#endif // LINE_ART_H
