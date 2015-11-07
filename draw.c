#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "render.h"
#include "colors.c"

/* Write the ppm-formatted file */
void write_ppm( char *filename, frameBuffer * fb )
{
    FILE *out = fopen (filename, "wb");
        fprintf( out, "P6\n%d %d\n255\n", fb->width, fb->height );
            
        // write the individual pixels in binary form
        //fwrite( fb->data, sizeof( pixel )*fb->width*fb->height, 1, out );
        pixel *pixelPtr = ( pixel *)fb->data;
        uint8_t rgb[3];

        for ( int row = 0; row < fb->height; row++ )
        {
            for ( int col = 0; col < fb->width; col++ )
            {
                rgb[0] = GET_R( pixelPtr[col] );
                rgb[1] = GET_G( pixelPtr[col] );
                rgb[2] = GET_B( pixelPtr[col] );
                fwrite( ( void *)&rgb[0], 3, 1, out );
            }
            pixelPtr += fb-> pixelStride;      
        }
            fclose( out );
}

/* Make the picture, store it, and exit */
int main ()
{
    //frameBuffer *fb =  createFrameBuffer( 320, 256, 0, 0, 0 );
    

    frameBuffer *fb2 =  createFrameBuffer( 320, 256, 0, 0, 0, 320 );
    //drawRectFrame( fb2, 1, 1,  100, 200, PINK );
    drawRectFill( fb2, 1, 1, 100, 200, PINK );
    write_ppm( "newR.ppm", fb2 );

    //frameBuffer *fb3 =  createFrameBuffer( 320, 256, 0, 0, 0, 1, 0 );
    //drawCircleFrame( fb3, 100, 100, 10, PINK );
    //write_ppm( "circleFrame.ppm", fb3 );

    //frameBuffer *fb4 =  createFrameBuffer( 320, 256, 0, 0, 0, 1, 0 );
    //drawEllipseFrame( fb4, 100, 100, 10, 20, PINK );
    //write_ppm( "ellipseFrame.ppm", fb4 );

    //frameBuffer *fb5 =  createFrameBuffer( 320, 256, 0, 0, 0, 320 );
    //drawTriangleFill( fb5, 20, 20, 50, 50, 10, 50, PINK );
    //drawTriangleFrame( fb5, 30, 50, 50, 20, 50, 20, 10, 20, 30, 50, 10, 20, PINK );
    //write_ppm( "triFill.ppm", fb5 );

    //frameBuffer *fb6 =  createFrameBuffer( 320, 256, 0, 0, 0, 1, 0 );
    //bezier(fb6, 350, 100, 550, 10, 600, 100, PINK);
    //write_ppm( "bezier.ppm", fb6 );

    //frameBuffer *fb7 =  createFrameBuffer( 320, 256, 0, 0, 0, 320 );
    //frameBuffer *dst = createFrameBuffer( 400, 340, 0, 0, fb7->data, fb7->pixelStride );
   
   // drawHorizontalLine( fb7, 50, 10, 20, PINK );
    //drawHorizontalLine( fb7, 50, 10, 30, RGBA(249, 54, 87, 100 ) );
    //drawHorizontalLine( fb7, 50, 10, 40, RGBA(249, 54, 87, 50) );
    //write_ppm( "lineTransp.ppm", fb7 );

    //bitBlt(dst, 20, 30, fb7, 10, 20, 60, 60 );
    //write_ppm ( "bitBltTest.ppm", dst );

    //frameBuffer *fb8 =  createFrameBuffer( 320, 256, 0, 0, 0, 1, 0 );
    //char *str = "hello world!";
    //drawText(fb8, 2, 10, str, PINK);
    //write_ppm ( "text.ppm", fb8 );

    // create a test for the coverPixel function
    return 0;
}
