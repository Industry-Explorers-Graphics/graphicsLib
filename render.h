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
FrameBuffer *createFrameBuffer( int width, int height );
void setPixel( FrameBuffer *fb, int x, int y, Pixel color );
void drawLine( FrameBuffer *fb );
void verticalLine( FrameBuffer *fb, int length, int x,  int y); 
