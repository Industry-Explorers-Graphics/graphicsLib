#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "render.c"

/* Write the ppm-formatted file */
void
write_ppm ( char *filename, frameBuffer * fb )
{
        FILE *out = fopen ( filename, "w" );
            fprintf ( out, "P6 %d %d %d\n", fb->width, fb->height, 255 );
                fwrite(fb->data, sizeof(Pixel)*fb->width*fb->height, 1, out);
                fclose ( out );
}

/* Make the picture, store it, and go home */
int
main ()
{
       frameBuffer * fb =  Create(320, 256);
       drawLine(fb);
       write_ppm ( "HEY.ppm", fb );
       return 0;
}
