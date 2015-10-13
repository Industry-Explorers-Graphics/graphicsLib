#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "render.h"

/* Write the ppm-formatted file */
void
write_ppm ( char *filename, FrameBuffer *fb )
{
        FILE *out = fopen ( filename, "w" );
        fprintf ( out, "P6 %d %d %d\n", fb->width, fb->height, 255 );
        fwrite( fb->data, sizeof(Pixel) * fb->width * fb->height, 1, out );
        fclose ( out );
}

/* Make the picture, store it, and go home */
int
main ()
{
       FrameBuffer *fb =  createFrameBuffer( 320, 256 );
       squaredRect( fb, 100, 50, 10, 5 );
       write_ppm ( "sRect.ppm", fb );
       return 0;
}
