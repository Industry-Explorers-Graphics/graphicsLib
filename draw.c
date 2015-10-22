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
    FrameBuffer *dst = createFrameBuffer(400, 340);
//    drawFillRect(fb, 1, 1,  100, 200, PINK);
//    drawCircle(fb, 100, 100, 10, PINK);
//    drawEllipse(fb, 100, 100, 10, 20, PINK);
//    triangle ( fb, 30, 50, 50, 20, 50, 20, 10, 20, 30, 50, 10, 20, PINK );
//    point(fb, 350, 100, RED);
//    point(fb, 550, 10, GREEN);
//    point(fb, 600, 100, BLUE);
//    bezier(fb, 350, 100, 550, 10, 600, 100, PINK);
//    write_ppm ( "bezier.ppm", fb );
    drawFillTriangle ( fb, 30, 50, 10, 20, 50, 40, PINK );
    bitBlt(dst, fb, 300, 200);
    write_ppm ( "bitBltTest.ppm", dst );
    return 0;
}