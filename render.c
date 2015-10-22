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

/* Does this work? */
/* Will need to be changed once we get rid of the pixel struct anyway */
Pixel getPixel(FrameBuffer *fb, int x, int y) {
    int offset = y * fb-> width + x;
    Pixel color = fb -> data[offset];
    return color;
}
// made this for testing purposes
void point(FrameBuffer * fb, int x, int y, Pixel color) {
    setPixel(fb, x, y, color);
}

/* Create  a horizontal line on FrameBuffer */
void drawHorizontalLine ( FrameBuffer *fb, int length, int x, int y, Pixel color )
{
    for( int i = x; i < ( x + length ); i++ )
    {
        setPixel( fb, i, y, color );
    }
}

/* Draw a vertical line */
void drawVerticalLine ( FrameBuffer *fb, int length, int x, int y, Pixel color )
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

void drawDiagonalLine ( FrameBuffer *fb, int x1, int y1, int x2, int y2, Pixel color )
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
void drawSquaredRect ( FrameBuffer *fb, int length, int width, int x, int y, Pixel color )
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

void drawFillRect(FrameBuffer * fb, int x, int y, int width, int height, Pixel color)
{
    for (int i = x; i <= (x + width); i++)
    {
        drawVerticalLine(fb, i, y, height, color);
    }
}

/* Create a triangle using the diagonal line function */
// Order is important for this implementation!
void drawTriangle ( FrameBuffer *fb,
        int ax1, int ay1, int ax2, int ay2,
        int bx1, int by1, int bx2, int by2,
        int cx1,  int cy1, int cx2, int cy2, Pixel color )
{
    drawDiagonalLine( fb, ax1, ay1, ax2, ay2, color );
    drawDiagonalLine( fb, bx1, by1, bx2, by2, color );
    drawDiagonalLine( fb, ax1, cy1, cx2, cy2, color );
}

/* Find the topmost vertex ( the one with the smallest y value ) of a polygon*/
int findTopmostPolyVertex( Point *poly, size_t numberOfElements )
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
void sortVerticesAscendingByY( Point *sorted, int x1, int y1, int x2, int y2, int x3, int y3 )
{
    Point vertices[3] = { { x1, y1 }, { x2, y2 }, { x3, y3 } };

    int topmost = findTopmostPolyVertex( vertices, 3 );

    // The topmost vertex should be the first Point
    sorted[0].x = vertices[topmost].x;
    sorted[0].y = vertices[topmost].y;

    // Sort the remaining two vertices
    switch (topmost)
    {
        case 0:
            if (vertices[1].y < vertices[2].y)
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
            if (vertices[0].y < vertices[2].y)
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
           if (vertices[0].y < vertices[1].y)
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
void drawFillTriangle ( FrameBuffer *fb,
        int x1, int y1,
        int x2, int y2,
        int x3, int y3, Pixel color )
{
    int a, b, y, last;

    // Sort three vertices so v1 is at top
    Point sorted[3];
    sortVerticesAscendingByY( sorted, x1, y1, x2, y2, x3, y3 );

	// Handle case if points form a horizontal line
    if (sorted[0].y == sorted[2].y)
	{
        a = b = sorted[0].x;

        if (sorted[1].x < a)
            a = sorted[1].x;
        else if (sorted[1].x > b)
            b = sorted[1].x;

        if (sorted[2].x < a)
            a = sorted[2].x;
        else if (sorted[2].x > b)
            b = sorted[2].x;

		drawHorizontalLine(fb, b - a + 1, a, sorted[0].y, color);
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
    // 0-1 and 0-2. If y1=y2 (flat-bottomed triangle), the scanline y1
	// is included here (and second loop will be skipped, avoiding a /0
	// error there), otherwise scanline y1 is skipped here and handled
	// in the second loop...which also avoids a /0 error here if y0=y1
	// (flat-topped triangle).
	if (sorted[1].y == sorted[2].y)
		last = sorted[1].y; // Include y1 scanline
	else
		last = sorted[1].y - 1; // Skip it

	for (y = sorted[0].y; y <= last; y++)
	{
		a = sorted[0].x + sa / dy01;
		b = sorted[0].x + sb / dy02;
		sa += dx01;
		sb += dx02;
		/* longhand:
		a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
		b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
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
		a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		*/
		if ( a > b )
			swap16( a, b );

		drawHorizontalLine(fb, b - a + 1, a, y, color);
	}
}

void drawCircle(FrameBuffer *fb, int x0, int y0, int radius, Pixel color)
{
  int x = radius;
  int y = 0;
  int decisionOver2 = 1 - x;

  while( y <= x )
  {
    setPixel(fb,  x + x0,  y + y0, color); // Octant 1
    setPixel(fb,  y + x0,  x + y0, color); // Octant 2
    setPixel(fb, -x + x0,  y + y0, color); // Octant 4
    setPixel(fb, -y + x0,  x + y0, color); // Octant 3
    setPixel(fb, -x + x0, -y + y0, color); // Octant 5
    setPixel(fb, -y + x0, -x + y0, color); // Octant 6
    setPixel(fb,  x + x0, -y + y0, color); // Octant 8
    setPixel(fb,  y + x0, -x + y0, color); // Octant 7
    y++;
    if (decisionOver2<=0)
    {
      decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
    }
    else
    {
      x--;
      decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
    }
  }
}

void drawEllipse (FrameBuffer * fb, int xc, int yc, int width, int height, Pixel color)
{
    int a2 = width * width;
    int b2 = height * height;
    int fa2 = 4 * a2, fb2 = 4 * b2;
    int x, y, sigma;

    /* first half */
    for (x = 0, y = height, sigma = 2*b2+a2*(1-2*height); b2*x <= a2*y; x++)
    {
        setPixel(fb, xc + x, yc + y, color);
        setPixel(fb, xc - x, yc + y, color);
        setPixel(fb, xc + x, yc - y, color);
        setPixel(fb, xc - x, yc - y, color);
        if (sigma >= 0)
        {
            sigma += fa2 * (1 - y);
            y--;
        }
        sigma += b2 * ((4 * x) + 6);
    }

    /* second half */
    for (x = width, y = 0, sigma = 2*a2+b2*(1-2*width); a2*y <= b2*x; y++)
    {
        setPixel(fb, xc + x, yc + y, color);
        setPixel(fb, xc - x, yc + y, color);
        setPixel(fb, xc + x, yc - y, color);
        setPixel(fb, xc - x, yc - y, color);
        if (sigma >= 0)
        {
            sigma += fb2 * (1 - x);
            x--;
        }
        sigma += a2 * ((4 * y) + 6);
    }
}

int getPt( int n1 , int n2 , float perc )
{
    int diff = n2 - n1;

    return n1 + ( diff * perc );
}

void bezier(FrameBuffer *fb, int x1, int y1, int x2, int y2, int x3, int y3, Pixel color) {
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

        setPixel(fb, x , y , color );
    }
}

/* Create a filled Polygon with Triangulation */
struct polygonDDA {
	int vertIndex;
	int vertNext;
	float x;
	float dx;
	int yStart;
	int yEnd;
}

void setupPolyDda( struct polygonDDA poly, float *vertices, int numOfVerts, int ivert, int dir )
	{
		poly.vertIndex = ivert;
		poly.vertNext = ivert + dir;
		if ( vertNext < 0 ) {
			poly.vertNext = numOfVerts - 1;
		}
		else if ( poly.vertNext == numOfVerts ){
			poly.vertNext = 0;
		}

		// set starting/ending ypos and current xpos
		poly.yStart = poly.yEnd;
		poly.yEnd = round(vertices[ poly.vertNext*2+1 ]);
		poly.x = vertices[poly.vertIndex*2+0];

		// Calculate fractional number of pixels to step in x (dx)
		float xdelta = vertices[ poly.vertNext*2+0 ] -
			vertices[ poly.vertIndex*2+0 ];
		int ydelta = poly.yEnd - poly.yStart;
		if (ydelta > 0) {
			poly.dx = xdelta / ydelta;
		}
		else {
			poly.dx = 0;
		}
	}
};

void polygonFill( FrameBuffer *fb, float *vertices, int numOfVerts, Pixel color )
{
	// find topmost vertex of the polygon
	int vMin = findTopmostVertex( vertices, numOfVerts );

	// set starting line
	polygonDDA leftDDA, rightDDA;
	int y = int( vertices[ vMin * 2 + 1 ] );
	leftDDA.yEnd = rightDDA.yEnd = y;

	// setup polygon scanner for left side, starting from top
	leftDDA.setupPolyDda( vertices, numOfVerts, vMin, +1 );

	// setup polygon scanner for right side, starting from top
	rightDDA.setupPolyDda( vertices, numOfVerts, vMin, -1 );

	while ( true )
	{
		if ( y >= leftDDA.yEnd )
		{
			if ( y >= rightDDA.yEnd )
			{
				if ( leftDDA.vertNext == rightDDA.vertNext )	{ // if same vertex, then done
					break;
				}

				int vNext = rightDDA.vertNext - 1;

				if ( vNext < 0 ) {
					vNext = numOfVerts - 1;
				}

				if ( vNext == leftDDA.vertNext )
				{
					break;
				}
			}
			leftDDA.setupPolyDda( vertices, numOfVerts, leftDDA.vertNext, +1 );	// reset left side
		}

		// check for right dda hitting end of polygon side
		// if so, reset scanner
		if ( y >= rightDDA.yEnd ) {
			rightDDA.setupPolyDda( vertices, numOfVerts, rightDDA.vertNext, -1 );
		}

		// fill span between two line-drawers, advance drawers when
		// hit vertices
		if ( y >= fb->y ) {
      int length = round( rightDDA.x ) - round( leftDDA.x );
			drawHorizontalLine( fb, length, round( leftDDA.x ), y, color );
		}

		leftDDA.x += leftDDA.dx;
		rightDDA.x += rightDDA.dx;

		// Advance y position.  Exit if run off its bottom
		y += 1;
		if ( y >= fb->y + fb->height )
		{
			break;
		}
	}
}
