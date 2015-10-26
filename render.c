#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "render.h"
#include "font.h"

/* Image functions */
frameBuffer *createFrameBuffer ( int width, int height, int x, int y, pixel *data, int ownsData, int pixelStride )
{
    frameBuffer *fb = ( frameBuffer * )malloc( sizeof( frameBuffer ) );
    fb->width = width;
    fb->height = height;
    fb->data = ( pixel * ) malloc( sizeof( pixel )* width * height );
    fb->x = x;
    fb->y = y;

    if ( data != NULL )
    {
        fb->data = data;
        fb->ownsData = 0; // why 0?
        fb->pixelStride = pixelStride;
    }
    else
    {
        fb->data = ( pixel *) malloc( sizeof( pixel )* width * height );
        fb->ownsData = 1;
        fb->pixelStride = width;
    }
    return fb;
}

/* With given x and y coordinates, give the pixels a color  */
void setPixel( frameBuffer *fb, int x, int y, pixel color )
{
    int offset = y * fb->width + x;
    fb->data[offset] = color;
}

/* Does this work? */
/* Will need to be changed once we get rid of the pixel struct anyway */
pixel getPixel( frameBuffer *fb, int x, int y ) {
    int offset = y * fb-> width + x;
    pixel color = fb -> data[offset];
    return color;
}
// made this for testing purposes
void points( frameBuffer * fb, int x, int y, pixel color ) {
    setPixel( fb, x, y, color );
}

/* Create a pixel cover function for blending */
void coverPixel( frameBuffer *fb, int x, int y, pixel color )
{
  uint8_t alpha = color.a;

	// Quick reject if the foreground pixel has both 0 opacity
	// and 0 for color component values
	if ( 0 == color ) {
		return;
	}

	if ( 0 == alpha ) {
		// Combine the colors, but don't
		// change the alpha of the background
	} else if ( 255 == alpha ) {
		// The foreground opacity is full, so set
		// the color
		// and set the background alpha to full as well
		setPixel( fb, x, y, color );
	} else {
		// All other cases where doing a cover of something
		// other than full opacity
		int32_t dstPixel = getPixel( fb, x, y );

		int dstColor = {
      lerp255( dstPixel.r, color.r, alpha ),
      lerp255( dstPixel.g, color.g, alpha ),
      lerp255( dstPixel.b, color.b, alpha ),
      lerp255( dstPixel.a, alpha, alpha )
    };
		setPixel( fb, x, y, dstColor );
	}
}

/* Create  a horizontal line on frameBuffer */
void drawHorizontalLine( frameBuffer *fb, int length, int x, int y, pixel color )
{
    for( int i = x; i < ( x + length ); i++ )
    {
        setPixel( fb, i, y, color );
    }
}

/* Draw a vertical line */
void drawVerticalLine( frameBuffer *fb, int length, int x, int y, pixel color )
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

void drawDiagonalLine( frameBuffer *fb, int x1, int y1, int x2, int y2, pixel color )
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
/* outline of rect function */
void drawRectFrame( frameBuffer *fb, int length, int width, int x, int y, pixel color )
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

void drawRectFill( frameBuffer * fb, int x, int y, int width, int height, pixel color )
{
    for ( int i = x; i <= ( x + width ); i++ )
    {
        drawVerticalLine( fb, i, y, height, color );
    }
}

/* Create a triangle using the diagonal line function */
// Order is important for this implementation!

typedef struct _point
{
    int x, y;
} point;

void drawTriangleFrame( frameBuffer *fb,
        int ax1, int ay1, int ax2, int ay2,
        int bx1, int by1, int bx2, int by2,
        int cx1,  int cy1, int cx2, int cy2, pixel color )
{
    drawDiagonalLine( fb, ax1, ay1, ax2, ay2, color );
    drawDiagonalLine( fb, bx1, by1, bx2, by2, color );
    drawDiagonalLine( fb, ax1, cy1, cx2, cy2, color );
}

/* Find the topmost vertex ( the one with the smallest y value ) of a polygon*/
int findTopmostPolyVertex( point *poly, size_t numberOfElements )
{
    int yMin = INT32_MAX;
    int vertexMin = 0;

    // Create an iterator
    size_t i = 0;
    while ( i < numberOfElements )
    {
        // If the y value of the current index is less
        // than the current value of yMin
        // set vertexMin to be the value at the idx location
        if (poly[i].y < yMin )
        {
            yMin = poly[i].y;
            vertexMin = i;
        }
        i++;
    }

    return vertexMin;
}

/* Sort Vertices by Ascending Y values */
void sortVerticesAscendingByY( point *sorted, int x1, int y1, int x2, int y2, int x3, int y3 )
{
    point vertices[3] = { { x1, y1 }, { x2, y2 }, { x3, y3 } };

    int topmost = findTopmostPolyVertex( vertices, 3 );

    // The topmost vertex should be the first point
    sorted[0].x = vertices[topmost].x;
    sorted[0].y = vertices[topmost].y;

    // Sort the remaining two vertices
    switch ( topmost )
    {
        case 0:
            if ( vertices[1].y < vertices[2].y )
            {
                sorted[1].x = vertices[1].x; sorted[1].y = vertices[1].y;
                sorted[2].x = vertices[2].x; sorted[2].y = vertices[2].y;
            }
            else
            {
                sorted[1].x = vertices[2].x; sorted[1].y = vertices[2].y;
                sorted[2].x = vertices[1].x; sorted[2].y = vertices[1].y;
            }
            break;

        case 1:
            if ( vertices[0].y < vertices[2].y )
            {
                sorted[1].x = vertices[0].x; sorted[1].y = vertices[0].y;
                sorted[2].x = vertices[2].x; sorted[2].y = vertices[2].y;
            }
            else
            {
                sorted[1].x = vertices[2].x; sorted[1].y = vertices[2].y;
                sorted[2].x = vertices[0].x; sorted[2].y = vertices[0].y;
            }
            break;

        case 2:
           if ( vertices[0].y < vertices[1].y )
           {
               sorted[1].x = vertices[0].x; sorted[1].y = vertices[0].y;
               sorted[2].x = vertices[1].x; sorted[2].y = vertices[1].y;
           }
           else
           {
               sorted[1].x = vertices[1].x; sorted[1].y = vertices[1].y;
               sorted[2].x = vertices[0].x; sorted[2].y = vertices[0].y;
           }
    }

}

/* Create a filled triangle  */
void drawTriangleFill( frameBuffer *fb,
        int x1, int y1,
        int x2, int y2,
        int x3, int y3, pixel color )
{
    int a, b, y, last;

    // Sort three vertices so v1 is at top
    point sorted[3];
    sortVerticesAscendingByY( sorted, x1, y1, x2, y2, x3, y3 );

	// Handle case if points form a horizontal line
    if ( sorted[0].y == sorted[2].y )
	{
        a = b = sorted[0].x;

        if ( sorted[1].x < a )
            a = sorted[1].x;
        else if ( sorted[1].x > b )
            b = sorted[1].x;

        if ( sorted[2].x < a )
            a = sorted[2].x;
        else if ( sorted[2].x > b )
            b = sorted[2].x;

		drawHorizontalLine( fb, b - a + 1, a, sorted[0].y, color );
        return;
    }

    int16_t
		dx01 = sorted[1].x - sorted[0].x,
		dy01 = sorted[1].y - sorted[0].y,
		dx02 = sorted[2].x - sorted[0].x,
		dy02 = sorted[2].y - sorted[0].y,
		dx12 = sorted[2].x - sorted[1].x,
		dy12 = sorted[2].y - sorted[1].y;

    int32_t sa = 0, sb = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2. If y1=y2 ( flat-bottomed triangle ), the scanline y1
	// is included here ( and second loop will be skipped, avoiding a /0
	// error there ), otherwise scanline y1 is skipped here and handled
	// in the second loop...which also avoids a /0 error here if y0=y1
	// ( flat-topped triangle ).
	if ( sorted[1].y == sorted[2].y )
		last = sorted[1].y; // Include y1 scanline
	else
		last = sorted[1].y - 1; // Skip it

	for ( y = sorted[0].y; y <= last; y++ )
	{
		a = sorted[0].x + sa / dy01;
		b = sorted[0].x + sb / dy02;
		sa += dx01;
		sb += dx02;
		/* longhand:
		a = x0 + ( x1 - x0 ) * ( y - y0 ) / ( y1 - y0 );
		b = x0 + ( x2 - x0 ) * ( y - y0 ) / ( y2 - y0 );
		*/

		if ( a > b ) swap16( a, b );
			drawHorizontalLine( fb, b - a + 1, a, y, color );
	}

	// For lower part of triangle, find scanline crossings for segments
	// 0-2 and 1-2. This loop is skipped if y1=y2.
	sa = dx12 * ( y - sorted[1].y );
	sb = dx02 * ( y - sorted[0].y );
	for ( ; y <= sorted[2].y; y++ )
	{
		a = sorted[1].x + sa / dy12;
		b = sorted[0].x + sb / dy02;
		sa += dx12;
		sb += dx02;
		/* longhand:
		a = x1 + ( x2 - x1 ) * ( y - y1 ) / ( y2 - y1 );
		b = x0 + ( x2 - x0 ) * ( y - y0 ) / ( y2 - y0 );
		*/
		if ( a > b )
			swap16( a, b );

		drawHorizontalLine( fb, b - a + 1, a, y, color );
	}
}

void drawCircleFrame( frameBuffer *fb, int x0, int y0, int radius, pixel color )
{
  int x = radius;
  int y = 0;
  int decisionOver2 = 1 - x;

  while( y <= x )
  {
    setPixel( fb,  x + x0,  y + y0, color ); // Octant 1
    setPixel( fb,  y + x0,  x + y0, color ); // Octant 2
    setPixel( fb, -x + x0,  y + y0, color ); // Octant 4
    setPixel( fb, -y + x0,  x + y0, color ); // Octant 3
    setPixel( fb, -x + x0, -y + y0, color ); // Octant 5
    setPixel( fb, -y + x0, -x + y0, color ); // Octant 6
    setPixel( fb,  x + x0, -y + y0, color ); // Octant 8
    setPixel( fb,  y + x0, -x + y0, color ); // Octant 7
    y++;
    if ( decisionOver2<=0 )
    {
      decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
    }
    else
    {
      x--;
      decisionOver2 += 2 * ( y - x ) + 1;   // Change for y -> y+1, x -> x-1
    }
  }
}

void drawEllipseFrame( frameBuffer * fb, int xc, int yc, int width, int height, pixel color )
{
    int a2 = width * width;
    int b2 = height * height;
    int fa2 = 4 * a2, fb2 = 4 * b2;
    int x, y, sigma;

    /* first half */
    for ( x = 0, y = height, sigma = 2 * b2 + a2 * ( 1-2 * height ); b2 * x <= a2 * y; x++ )
    {
        setPixel( fb, xc + x, yc + y, color );
        setPixel( fb, xc - x, yc + y, color );
        setPixel( fb, xc + x, yc - y, color );
        setPixel( fb, xc - x, yc - y, color );
        if ( sigma >= 0 )
        {
            sigma += fa2 * ( 1 - y );
            y--;
        }
        sigma += b2 * ( ( 4 * x ) + 6 );
    }

    /* second half */
    for ( x = width, y = 0, sigma = 2 * a2 + b2 * ( 1-2 * width ); a2 * y <= b2 * x; y++ )
    {
        setPixel( fb, xc + x, yc + y, color );
        setPixel( fb, xc - x, yc + y, color );
        setPixel( fb, xc + x, yc - y, color );
        setPixel( fb, xc - x, yc - y, color );
        if ( sigma >= 0 )
        {
            sigma += fb2 * ( 1 - x );
            x--;
        }
        sigma += a2 * ( ( 4 * y ) + 6 );
    }
}

int getPt( int n1 , int n2 , float perc )
{
    int diff = n2 - n1;

    return n1 + ( diff * perc );
}

void bezier( frameBuffer *fb, int x1, int y1, int x2, int y2, int x3, int y3, pixel color ) {
    for( float i = 0 ; i < 1 ; i += 0.01 )
    {
        // The Green Line
        int xa = getPt( x1 , x2 , i );
        int ya = getPt( y1 , y2 , i );
        int xb = getPt( x2 , x3 , i );
        int yb = getPt( y2 , y3 , i );

        // The Black Dot
        int x = getPt( xa , xb , i );
        int y = getPt( ya , yb , i );

        setPixel( fb, x , y , color );
    }
}

/* Create Bit Blt */
int fb_contains(frameBuffer *fb, int x, int y)
{
    return x >= (int) fb->x && x < (int) fb->x + (int)fb->width && y >=  (int) fb->y && y < (int) fb->y + fb->height;
}

void bitBlt( frameBuffer *dst, int dstx, int dsty, frameBuffer *src, int srcx, int srcy, int srcWidth, int srcHeight )
{
    for (int col = srcx; col < src->width; col++)
    {
        for (int row = srcy; row < src->height; row++)
        {
            if (fb_contains(dst, dstx + col, dsty + row))
                setPixel(dst, dstx + col, dsty + row, getPixel(src, col, row));
        }
    }

}


/* Original Bit Blit function for historical purposes */
/* int fb_contains(FrameBuffer *fb, int x, int y) {
    return x >= (int) fb->x && x < (int) fb->x + (int)fb->width && y >=  (int) fb->y && y < (int) fb->y + fb->height;
}

void bitBlt(FrameBuffer *dst, FrameBuffer *src, int x, int y) {
    for (int col = 0; col < src->width; col++) {
        for (int row = 0; row < src->height; row++) {
            if (fb_contains(dst, x + col, y + row)) {
                setPixel(dst, x + col, y + row, getPixel(src, col, row));
           }
        }
    }
}
*/

void drawText(frameBuffer *fb, int px, int py, char* text, pixel color) {
    // change to global font width and height defined in file
    px = px* 8;
    py = py* 15;

    for (int c = 0; text[c] != '\0'; c++ )
    {
            for (int i = 0; i < 15; i += 1)
            {
                int sym = iso_font[text[c]*16+i];

                int x = px;
                int y = py + i;

                for (int ii =0; ii < 8; ii++)
                {
                    x+=1;
                    if ((sym & (1 << ii)))
                    {
                       setPixel(fb, x, y, color);
                    }
                }
            }
            px+=8;
    }
}
