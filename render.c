#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "render.h"

/* Image functions */
FrameBuffer *createFrameBuffer ( int width, int height )
{
    FrameBuffer *fb = ( FrameBuffer *)malloc( sizeof( FrameBuffer ));
    fb->width = width;
    fb->height = height;
    fb->data = ( Pixel *) malloc( sizeof(Pixel)* width * height );

    return fb;
}

/* With given x and y coordinates, give the pixels a color  */
void setPixel ( FrameBuffer *fb, int x, int y, Pixel color )
{
    int offset = y * fb->width + x;
    fb->data[offset] = color;
}

/* Return color when pixel location is given */
int getPixel ( FrameBuffer *fb, int x, int y)
{
       
}

/* Draw a line on FrameBuffer */
void horizontalLine ( FrameBuffer *fb, int length, int x, int y )
{
    for( int i = x; i < ( x + length ); i++ )
    {
        setPixel( fb, i, y, PINK );
    }
}

/* Draw a vertical line */
void verticalLine ( FrameBuffer *fb, int length, int x, int y )
{
    for( int i = y; i < ( y + length ); i++ )
    {
        setPixel( fb, x, i, PINK );
    }
}

/* Draw a diagonal line using the Bresenham line algorithm */
/* Check the sign of a number */
int sign( int number )
{
    if ( number < 0 ) 
    { 
        return -1;
    }
    else if ( number >= 0 ) 
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

void diagonalLine ( FrameBuffer *fb, int x1, int y1, int x2, int y2, Pixel color ) 
{
    
    int i, dx, dy, sdx, sdy, dxabs, dyabs, x, y, xStart, yStart;
    /* Calculate the horizontal distance from the line */
    dx = x2 - x1;
    // Calculate the vertical distace from the line
    dy = y2 - y1;
    // Find the absolute values of the line distances
    dxabs = abs( dx );
    dyabs = abs( dy );
    // Return the sign of the distances and save
    sdx = sign( dx );
    sdy = sign( dy );
    // Use a bitwise shift operation?
    x = dyabs >> 1;
    y = dxabs >> 1;
    // Declare where the line should start
    xStart = x1;
    yStart = y1;

    if ( dxabs >= dyabs ) /* the line is more horizontal than vertical */
    {
        for ( i = 0; i < dxabs; i++ )
        {
            y += dyabs;
            if ( y >= dxabs )
            {
                y -= dxabs;
                yStart += sdy;
            }
            xStart += sdx;
            setPixel( fb,  xStart, yStart, PINK  );
        }
    }
    else
    {
        for ( i=0; i < dyabs; i++ )
        {
            x += dxabs;
            if ( x >= dyabs )
            {
                x -= dyabs;
                xStart += sdx;
            }
            yStart += sdy;
            setPixel( fb, xStart, yStart, PINK );
        }
    }
}


/* Draw a rectangle with square corners*/
void squaredRect ( FrameBuffer *fb, int length, int width, int x, int y )
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

/* Draw a rectangle with rounded corners  */


