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
// I'm still working on this
Pixel getPixel ( FrameBuffer *fb, int x, int y)
{
    //return Pixel color;      
}

/* Create  a horizontal line on FrameBuffer */
void horizontalLine ( FrameBuffer *fb, int length, int x, int y, Pixel color )
{
    for( int i = x; i < ( x + length ); i++ )
    {
        setPixel( fb, i, y, color );
    }
}

/* Draw a vertical line */
void verticalLine ( FrameBuffer *fb, int length, int x, int y, Pixel color )
{
    for( int i = y; i < ( y + length ); i++ )
    {
        setPixel( fb, x, i, color );
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
            setPixel( fb,  xStart, yStart, color );
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
            setPixel( fb, xStart, yStart, color );
        }
    }
}


/* Draw a rectangle with square corners*/
void squaredRect ( FrameBuffer *fb, int length, int width, int x, int y, Pixel color )
{
   if ( length > 0 && width > 0 )
   {
        for( int i = x; i < ( x + length ); i++ )
        {   
            setPixel( fb, i, y, color );
            setPixel( fb, i, ( y + width ), color );
        }

        for( int j = y; j < ( y + width ); j++ )
        {
            setPixel( fb, x, j, color );
            setPixel( fb, ( x + length ), j, color );
        }
        
    }
}

/* Create a rectangle with rounded corners  */

/* Create a triangle using the diagonal line function */
// Order is important for this implementation!
void triangle ( FrameBuffer *fb, int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2, int cx1,  int cy1, int cx2, int cy2, Pixel color )
{
    diagonalLine( fb, ax1, ay1, ax2, ay2, color );
    diagonalLine( fb, bx1, by1, bx2, by2, color );
    diagonalLine( fb, ax1, cy1, cx2, cy2, color );
}

void triangle (   )
{
    drawTriangle()
    {
        /* at first sort the three vertices by y-coordinate ascending so v1 is the topmost vertice */
          sortVerticesAscendingByY();

        /* here we know that v1.y <= v2.y <= v3.y */
        /* check for trivial case of bottom-flat triangle */
        if (v2.y == v3.y)
                  {
                          fillBottomFlatTriangle(v1, v2, v3);
                            }
        /* check for trivial case of top-flat triangle */
        else if (vt1.y == vt2.y)
                    {
                            fillTopFlatTriangle(g, vt1, vt2, vt3);
                              } 
        else
        {
                              /* general case - split the triangle in a topflat and bottom-flat one */
                              Vertice v4 = new Vertice( 
                                            (int)(vt1.x + ((float)(vt2.y - vt1.y) / (float)(vt3.y - vt1.y)) * (vt3.x - vt1.x)), vt2.y);
                                  fillBottomFlatTriangle(g, vt1, vt2, v4);
                                      fillTopFlatTriangle(g, vt2, v4, vt3);
                                        }
    }
