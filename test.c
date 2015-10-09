#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/* Image parameters */
#define W 320
#define H 256
#define M 255

/* This is where we'll store the pixels */
struct pixel { uint8_t r, g, b, a; };
struct pixel fb[W][H];

/* Draw a pink line */
void
create_image ( void )
{
    struct pixel PINK;
    PINK.r = 240;
    PINK.g = 54;
    PINK.b = 87;
    PINK.a = 0;

        /* Run the width of the image */
        for ( int x=0; x<W; x++ )
        {
            int y = H/2;
            /* Give the line the color PINK */
            fb[x][y] = PINK;
        }
}

/* Write the ppm-formatted file */
void
write_ppm ( char *filename )
{
        FILE *out = fopen ( filename, "w" );
            /* Header:
             * Magic number, width, height, maxvalue
             */
            fprintf ( out, "P6 %d %d %d\n", W, H, M );
                /* Rows. 2-byte values if max > 255, 1-byte otherwise.
                 * These loops explicitly show where every single byte
                 * goes; in practice, it would be faster and shorter to
                 * interleave the arrays and write bigger blocks of
                 * contiguous data.
                 */
                for ( size_t i=0; i<H; i++ )
                            for ( size_t j=0; j<W; j++ )
                            {
                            }
                fclose ( out );
}

/* Make the picture, store it, and go home */
int
main ()
{
        create_image();
            write_ppm ( "test.ppm" );
                exit ( EXIT_SUCCESS );
}
