#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/* Image parameters */
/* Create the pixel bytes */
typedef struct pixel 
{ 
    uint8_t r, g, b; 
} Pixel;

typedef struct frameBuffer
{
    int width;
    int height;
    Pixel *data;
} frameBuffer;


/* Support the frame buffer*/
frameBuffer *fb;

/* Image functions */
frameBuffer * Create( int width, int height )
{
    frameBuffer *fb = (frameBuffer *)malloc(sizeof(frameBuffer));
    fb-> width = width;
    fb-> height = height;
    fb-> data = (Pixel *) malloc(sizeof(Pixel)* width * height);

    return fb;
}


/*Create a color to test*/
Pixel PINK = 
{    
     240, 54, 87
};

/* Create a drawing on frame buffer  */
void SetPixel(frameBuffer *fb, int x, int y, Pixel color)
{
    int offset = y * fb-> width + x;
    fb -> data[offset] = color;
}

void drawLine(frameBuffer * fb) 
{
    for (int x = 10; x < 60; x++ )
    {
        SetPixel(fb, x, 10, PINK);
    }
}


/* Write the ppm-formatted file */
void
write_ppm ( char *filename, frameBuffer * fb )
{
        FILE *out = fopen ( filename, "w" );
            /* Header:
             * Magic number, width, height, maxvalue
             */
            fprintf ( out, "P6 %d %d %d\n", fb->width, fb->height, 255 );
                /* Rows. 2-byte values if max > 255, 1-byte otherwise.
                 * These loops explicitly show where every single byte
                 * goes; in practice, it would be faster and shorter to
                 * interleave the arrays and write bigger blocks of
                 * contiguous data.
                 */
                            
                fwrite(fb->data, sizeof(Pixel)*fb->width*fb->height, 1, out);
                            
                fclose ( out );
}

/* Make the picture, store it, and go home */
int
main ()
{
       frameBuffer * fb =  Create(320, 256);
       drawLine(fb);

       
            write_ppm ( "sine.ppm", fb );
            return 0;
}
