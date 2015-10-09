#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "render.h"

/* Image functions */
FrameBuffer *createFrameBuffer( int width, int height )
{
    FrameBuffer *fb = ( FrameBuffer *)malloc( sizeof( FrameBuffer ));
    fb->width = width;
    fb->height = height;
    fb->data = (Pixel *) malloc( sizeof(Pixel)* width * height );

    return fb;
}

/* Create a drawing on frame buffer  */
void setPixel( FrameBuffer *fb, int x, int y, Pixel color )
{
    int offset = y * fb->width + x;
    fb->data[offset] = color;
}

void drawLine( FrameBuffer *fb )
{
    for ( int x = 10; x < 60; x++ )
    {
        setPixel( fb, x, 10, PINK );
    }
}

