#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "render.h"

/* Write the ppm-formatted file */
void write_ppm(char *filename, FrameBuffer * fb)
{
    FILE *out = fopen (filename, "w");
        fprintf(out, "P6 %d %d %d\n", fb->width, fb->height, 255 );
            fwrite(fb->data, sizeof(Pixel)*fb->width*fb->height, 1, out);
            fclose(out);
}

/* Make the picture, store it, and go home */
int main ()
{
    FrameBuffer *fb =  createFrameBuffer( 320, 256 );
//    FrameBuffer *dst = createFrameBuffer(400, 340);
//    drawFillRect(fb, 1, 1,  100, 200, PINK);
//    drawCircle(fb, 100, 100, 10, PINK);
//    drawEllipse(fb, 100, 100, 10, 20, PINK);
//    triangle ( fb, 30, 50, 50, 20, 50, 20, 10, 20, 30, 50, 10, 20, PINK );
//    point(fb, 350, 100, RED);
//    point(fb, 550, 10, GREEN);
//    point(fb, 600, 100, BLUE);
//    bezier(fb, 350, 100, 550, 10, 600, 100, PINK);
//    write_ppm ( "bezier.ppm", fb );
//    drawFillTriangle ( fb, 30, 50, 10, 20, 50, 40, PINK );
//    bitBlt(dst, fb, 300, 200);
//    for (int i = 0; i < 40; i++) {
//      drawChar(fb, i, 0, i + 100, GREEN);
//    }
      // HELLO WORLD
//    drawChar(fb, 0, 10, 72, GREEN);
//    drawChar(fb, 1, 10, 69, GREEN);
//    drawChar(fb, 2, 10, 76, GREEN);
//    drawChar(fb, 3, 10, 76, GREEN);
//    drawChar(fb, 4, 10, 79, GREEN);
//    drawChar(fb, 5, 10, 130, GREEN);
//    drawChar(fb, 6, 10, 0, GREEN);
//    drawChar(fb, 7, 10, 87, GREEN);
//    drawChar(fb, 8, 10, 79, GREEN);
//    drawChar(fb, 9, 10, 82, GREEN);
//    drawChar(fb, 10, 10, 76, GREEN);
//    drawChar(fb, 11, 10, 68, GREEN);
//    drawChar(fb, 12, 10, 33, GREEN);
    char *str = "hello world!";
    drawText(fb, 2, 10, str, GREEN);
    write_ppm ( "text.ppm", fb );
    return 0;
}