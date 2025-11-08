
#include <stdio.h>
#include <stdlib.h>
#include "simple_image.h"
#include "line_art.h"

#define PRINTER_X0 36.5
#define PRINTER_Y0 40.0
#define PRINTER_Z0 5.0
#define PRINTER_FEEDRATE 720.0

FILE *init_gcode(const char *filename) {
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("[ERROR] failed to open: %s!\n", filename);
    }

    fprintf(fp, "M862.3 P \"MK3S\" ; printer model check\n");
    fprintf(fp, "G21 ; set units to millimeters\n");
    fprintf(fp, "G90 ; use absolute coordinates\n");
    fprintf(fp, "G28 W ; home all without mesh bed level\n");
    
    fprintf(fp, "\n");
    fprintf(fp, "G1 X%f Y%f, Z%f, F%f\n",
            PRINTER_X0, PRINTER_Y0, PRINTER_Z0, PRINTER_FEEDRATE);
    fprintf(fp, "G92 X0 Y0 Z0 ; set current position to origin\n");
    fprintf(fp, "\n");

    return fp;
}

void close_gcode(FILE *fp) {
    fprintf(fp, "\n");
    fprintf(fp, "M84 ; disable motors\n");
    fclose(fp);
}

void goto_gcode(FILE *fp, uint32_t x, uint32_t y) {
    fprintf(fp, "G1 X%d Y%d\n", x, y);
}

void draw_image(const image_t *img, const frame_t *frame, FILE *gcode) {
    line_t line = darkest_line(img, frame);

    // show_line(&line);
    brighten_line(img, line.start.x, line.start.y, line.end.x, line.end.y);
    goto_gcode(gcode, line.start.x, line.start.y);
    goto_gcode(gcode, line.end.x, line.end.y);

    for (uint32_t i = 0; i < MAX_LINES; i++) {
        line_t next = next_line(img, frame, &line);

        if ((next.start.x == next.end.x) && (next.start.y == next.end.y)) {
            printf("[INFO]: Stopping at %d\n", i);
            break;
        }

        line = next;
        // show_line(&line);
        brighten_line(img, line.start.x, line.start.y, line.end.x, line.end.y);
        goto_gcode(gcode, line.end.x, line.end.y);
    }
}

int main (void) {
    char *input    = "smiley-face.jpg";
    char *output   = "Result.jpg";
    char *drawing  = "draw.gcode";

    image_t img = load_image(input);

    if (img.data == NULL) {
        return 1;
    }

    image_t out = to_gray(&img);
    
    if (out.data == NULL) {
        return 1;
    }

    FILE *gcode = init_gcode(drawing);

    printf("[INFO] Loading file: %s\n", input);
    printf("[INFO] Image width:  %d\n", img.width);
    printf("[INFO] Image height: %d\n", img.height);

    frame_t frame = init_round_frame(&out, MIN(out.width, out.height)/2, 1);

    draw_image(&out, &frame, gcode);

    printf("[INFO] Saving: %s\n", output);
    save_image(&out, output);

    free_image(&img);
    free_image(&out);
    free(frame.nails);
    close_gcode(gcode);

    return 0;
}
