#include "render.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/* Image functions */
frameBuffer * Create( int width, int height )
{
    frameBuffer *fb = (frameBuffer *)malloc(sizeof(frameBuffer));
    fb-> width = width;
    fb-> height = height;
    fb-> data = (Pixel *) malloc(sizeof(Pixel)* width * height);

    return fb;
}

/* Create a drawing on frame buffer  */
void SetPixel(frameBuffer *fb, int x, int y, Pixel color)
{
    int offset = y * fb-> width + x;
    fb -> data[offset] = color;
}

void drawLine(frameBuffer * fb)
{
    for (int x = 10; x < 60; x++ )
    {
        SetPixel(fb, x, 10, PINK);
    }
}

