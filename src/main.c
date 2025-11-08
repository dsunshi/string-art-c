
#include <stdio.h>
#include <stdlib.h>
#include "simple_image.h"
#include "line_art.h"

void draw_image(const image_t *img, const frame_t *frame) {
    line_t line = darkest_line(img, frame);

    show_line(&line);
    brighten_line(img, line.start.x, line.start.y, line.end.x, line.end.y);
    for (uint32_t i = 0; i < MAX_LINES; i++) {
        line_t next = next_line(img, frame, &line);

        line = next;
        brighten_line(img, line.start.x, line.start.y, line.end.x, line.end.y);
        show_line(&line);
    }
}

int main (void) {
    char *input  = "smiley-face.jpg";
    char *output = "Result.jpg";

    image_t img = load_image(input);

    if (img.data == NULL) {
        return 1;
    }

    image_t out = to_gray(&img);
    
    if (out.data == NULL) {
        return 1;
    }

    printf("[INFO] Loading file: %s\n", input);
    printf("[INFO] Image width:  %d\n", img.width);
    printf("[INFO] Image height: %d\n", img.height);

    frame_t frame = init_round_frame(&out, MIN(out.width, out.height)/2, 1);

    draw_image(&out, &frame);

    printf("[INFO] Saving: %s\n", output);
    save_image(&out, output);

    free_image(&img);
    free_image(&out);
    free(frame.nails);

    return 0;
}
