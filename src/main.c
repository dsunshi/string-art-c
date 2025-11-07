
#include <stdio.h>
#include <stdlib.h>
#include "simple_image.h"
#include "line_art.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int main (void) {
    char *input  = "smiley-face.jpg";
    char *output = "Result.jpg";

    image_t img = load_image(input);
    image_t out = to_gray(&img);

    printf("[INFO] Loading file: %s\n", input);
    printf("[INFO] Image width: %d\n", img.width);
    printf("[INFO] Image height: %d\n", img.height);

    frame_t frame = init_round_frame(&out, MIN(out.width, out.height)/2, 1);

    brighten_line(&out, 10, 10, 300, 300);
    // clear_image(&out, (pixel_t){0xff, 0xff, 0xff});
    // draw_line(&out, 0, 0, 250, 250, (pixel_t){0x00, 0x00, 0x00});
    // draw_line(&out, 250, 250, 500, 0, (pixel_t){0x00, 0x00, 0x00});

    // for (int y = 0; y < img.height; y++) {
    //     for (int x = 0; x < img.width; x++) {
    //         pixel_t p = pixel_at(&img, x, y);
    //         show_pixel(&p);
    //     }
    // }

    printf("[INFO] Saving: %s\n", output);
    save_image(&out, output);

    free_image(&img);
    free_image(&out);
    free(frame.nails);

    return 0;
}
