#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#ifndef render_h
#define render_h

#define swap16( a, b ) { int16_t t = a; a = b; b = t; }

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
    int *x;
    int *y;
} FrameBuffer;

/* Create a point */
typedef struct point
{
    int x;
    int y;
} Point;

static const Pixel PINK = { 240, 54, 87 };
static const Pixel RED = { 250, 0, 0 };
static const Pixel ORANGE = { 255, 122, 0 };
static const Pixel YELLOW = { 255, 211, 0 };
static const Pixel GREEN = { 0, 250, 0 };
static const Pixel BLUE = { 0, 0, 250 };
static const Pixel PURPLE = { 119, 3, 173 };
static const Pixel WHITE = { 255, 255, 255 };
static const Pixel BLACK = { 0, 0, 0 };

FrameBuffer *createFrameBuffer ( int width, int height );
//Pixel getPixel(FrameBuffer * fb, int x, int y);

void point(FrameBuffer * fb, int x, int y, Pixel color);

void drawHorizontalLine ( FrameBuffer *fb, int length, int x, int y, Pixel color );
void drawVerticalLine ( FrameBuffer *fb, int length, int x,  int y, Pixel color );
void drawDiagonalLine ( FrameBuffer *fb, int x1, int y1, int x2, int y2, Pixel color );

void drawSquaredRect ( FrameBuffer *fb, int length, int width, int x, int y, Pixel color );
void drawFillRect(FrameBuffer * fb, int x, int y, int width, int height, Pixel color);

void drawTriangle ( FrameBuffer *fb, int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2, int cx1,  int cy1, int cx2, int cy2, Pixel color );
void drawFillTriangle ( FrameBuffer *fb, int x1, int y1, int x2, int y2, int x3, int y3, Pixel color );

void drawCircle(FrameBuffer *fb, int x0, int y0, int radius, Pixel color);
void drawEllipse (FrameBuffer * fb, int xc, int yc, int width, int height, Pixel color);

void bezier(FrameBuffer *fb, int x1, int y1, int x2, int y2, int x3, int y3, Pixel color);

void polygonFill( FrameBuffer *fb, float *vertices, int numOfVerts, Pixel color);

void bitBlt(FrameBuffer *dst, FrameBuffer *src, int x, int y);

#endif
