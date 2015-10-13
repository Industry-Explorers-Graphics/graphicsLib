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

/* With given x and y coordinates, give the pixels a color  */
void setPixel( FrameBuffer *fb, int x, int y, Pixel color )
{
    int offset = y * fb->width + x;
    fb->data[offset] = color;
}

/* Return color when pixel location is given */


/* Draw a line on FrameBuffer */
void horizontalLine( FrameBuffer *fb, int length, int x, int y )
{
    for( int i = x; i < ( x + length); i++ )
    {
        setPixel( fb, i, y, PINK );
    }
}

/* Draw a vertical line */
void verticalLine( FrameBuffer *fb, int length, int x, int y)
{
    for( int i = y; i < ( y + length); i++ )
    {
        setPixel( fb, x, i, PINK );
    }
}

/* Draw a rectangle with square corners*/
void squaredRect( FrameBuffer *fb, int length, int width, int x, int y )
{
   if ( length > 0 && width > 0 )
   {
        for( int i = x; i < ( x + length ); i++ )
        {   
            setPixel( fb, i, y, PINK );
            setPixel( fb, i, (y + width), PINK );
        }

        for( int j = y; j < ( y + width ); j++ )
        {
            setPixel( fb, x, j, PINK );
            setPixel( fb, (x + length), j, PINK );
        }
        
    }
}
