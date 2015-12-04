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
    frameBuffer *fb2 =  createFrameBuffer( 0, 0, 400, 600, 0, 400 );
    //drawRectFrame( fb2, 1, 1,  100, 200, PINK );
    drawRectFill( fb2, 0, 0, 10, 20, PINK );
    write_ppm( "newR.ppm", fb2 );

    frameBuffer *fb3 = createFrameBuffer( 0, 0, 400, 600, 0, 400 );
    drawText( fb3, 0, 0, "hey", WHITE );
    write_ppm( "text.ppm", fb3 );

    frameBuffer *fb4 = createFrameBuffer( 0, 0, 400, 600, 0, 400 );
    points( fb4, 0, 0, GREEN );
    write_ppm( "pixel.ppm", fb4 );
    return 0;
}
