#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#ifndef render_h
#define render_h

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
} FrameBuffer;

typedef struct _point
{
    int x;
    int y;
} point;

static const point pt = { x, y };

static const Pixel PINK = { 240, 54, 87 };
FrameBuffer *createFrameBuffer ( int width, int height );
//Pixel getPixel(FrameBuffer * fb, int x, int y);

void drawHorizontalLine ( FrameBuffer *fb, int length, int x, int y, Pixel color );
void drawVerticalLine ( FrameBuffer *fb, int length, int x,  int y, Pixel color );
void drawDiagonalLine ( FrameBuffer *fb, int x1, int y1, int x2, int y2, Pixel color );

void drawSquaredRect ( FrameBuffer *fb, int length, int width, int x, int y, Pixel color );
void drawFillRect(FrameBuffer * fb, int x, int y, int width, int height, Pixel color);

//void triangle ( FrameBuffer *fb, int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2, int cx1, int cy1, int cx2, int cy2, Pixel color );
//void drawTriangle ( FrameBuffer *fb, int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2, int cx1,  int cy1, int cx2, int cy2, Pixel color );

void drawCircle(FrameBuffer *fb, int x0, int y0, int radius, Pixel color);
void drawEllipse (FrameBuffer * fb, int xc, int yc, int width, int height, Pixel color);

#endif
