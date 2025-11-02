
// #include <stdio.h>
#include "simple_image.h"

int main (void) {
    char *input  = "smiley-face.jpg";
    char *output = "Result.jpg";

    image_t img = load_image(input);
    image_t out = to_gray(&img);

    // clear_image(&out, (pixel_t){0xff, 0xff, 0xff});
    // draw_line(&out, 0, 0, 250, 250, (pixel_t){0x00, 0x00, 0x00});
    // draw_line(&out, 250, 250, 500, 0, (pixel_t){0x00, 0x00, 0x00});

    // for (int y = 0; y < img.height; y++) {
    //     for (int x = 0; x < img.width; x++) {
    //         pixel_t p = pixel_at(&img, x, y);
    //         show_pixel(&p);
    //     }
    // }

    save_image(&out, output);

    free_image(&img);
    free_image(&out);

    return 0;
}
