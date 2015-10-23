#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "render.h"

/* Write the ppm-formatted file */
void write_ppm(char *filename, frameBuffer * fb)
{
    FILE *out = fopen (filename, "w");
        fprintf(out, "P6 %d %d %d\n", fb->width, fb->height, 255 );
            fwrite( fb->data, sizeof( pixel )*fb->width*fb->height, 1, out );
            fclose(out);
}

/* Make the picture, store it, and o home */
int main ()
{
    frameBuffer *fb =  createFrameBuffer( 320, 256 );
    frameBuffer *dst = createFrameBuffer( 400, 340 );

    frameBuffer *fb2 =  createFrameBuffer( 320, 256 );
    drawRectFrame( fb2, 1, 1,  100, 200, PINK );
    write_ppm( "rectFrame.ppm", fb2 );

    frameBuffer *fb3 =  createFrameBuffer( 320, 256 );
    drawCircleFrame( fb3, 100, 100, 10, PINK );
    write_ppm( "circleFrame.ppm", fb3 );

    frameBuffer *fb4 =  createFrameBuffer( 320, 256 );
    drawEllipseFrame( fb4, 100, 100, 10, 20, PINK );
    write_ppm( "ellipseFrame.ppm", fb4 );

    frameBuffer *fb5 =  createFrameBuffer( 320, 256 );
    drawTriangleFrame( fb5, 30, 50, 50, 20, 50, 20, 10, 20, 30, 50, 10, 20, PINK );
    write_ppm( "triFrame.ppm", fb5 );

    //points(fb, 350, 100, RED);
    //points(fb, 550, 10, GREEN);
    //points(fb, 600, 100, BLUE);

    frameBuffer *fb6 =  createFrameBuffer( 320, 256 );
    bezier(fb6, 350, 100, 550, 10, 600, 100, PINK);
    write_ppm( "bezier.ppm", fb6 );

    frameBuffer *fb7 =  createFrameBuffer( 320, 256 );
    drawTriangleFill( fb7, 30, 50, 10, 20, 50, 40, PINK );
    write_ppm( "trianleFrame.ppm", fb7 );

    bitBlt(dst, fb, 300, 200);
    write_ppm ( "BitBlt.ppm", dst );
    return 0;
}
