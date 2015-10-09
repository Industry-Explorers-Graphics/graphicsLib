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
} frameBuffer;

Pixel PINK =
{
     240, 54, 87
};
