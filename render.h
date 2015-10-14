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
} FrameBuffer;

static const Pixel PINK = { 240, 54, 87 };
FrameBuffer *createFrameBuffer ( int width, int height );
void horizontalLine ( FrameBuffer *fb, int length, int x, int y, Pixel color );
void verticalLine ( FrameBuffer *fb, int length, int x,  int y, Pixel color );
void squaredRect ( FrameBuffer *fb, int length, int width, int x, int y, Pixel color );
void diagonalLine ( FrameBuffer *fb, int x1, int y1, int x2, int y2, Pixel color );
void triangle ( FrameBuffer *fb, int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2, int cx1, int cy1, int cx2, int cy2, Pixel color );
