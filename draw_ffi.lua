#define swap16( a, b ) { int16_t t = a; a = b; b = t; }

// turn a division by 255 into something
// much cheaper to calculate
// for values between 0 and 65534
#define div255( num ) ( ( num + ( num >> 8 ) ) >> 8 )
#define lerp255( background, foreground, a ) ( ( uint8_t )div255( ( foreground * a + background * ( 255-a ) ) ) )

/* Image parameters */
/* Create the pixel bytes */
typedef struct _pixel
{
    uint8_t r, g, b, a;
} pixel;

typedef struct _frameBuffer
{
    int width;
    int height;
    pixel *data;
    int x;
    int y;
    int ownsData;
    int pixelStride;
} frameBuffer;

static const pixel PINK = { 240, 54, 87, 100 };
static const pixel RED = { 250, 0, 0, 1 };
static const pixel ORANGE = { 255, 122, 0, 1 };
static const pixel YELLOW = { 255, 211, 0, 1 };
static const pixel GREEN = { 0, 250, 0, 1 };
static const pixel BLUE = { 0, 0, 250, 1 };
static const pixel PURPLE = { 119, 3, 173, 1 };
static const pixel WHITE = { 255, 255, 255, 1 };
static const pixel BLACK = { 0, 0, 0, 1 };

frameBuffer *createFrameBuffer ( int width, int height, int x, int y, pixel *data, int ownsData, int pixelStride );

void drawHorizontalLine( frameBuffer *fb, int length, int x, int y, pixel color );
void drawVerticalLine( frameBuffer *fb, int length, int x,  int y, pixel color );
void drawDiagonalLine( frameBuffer *fb, int x1, int y1, int x2, int y2, pixel color );

void drawRectFrame( frameBuffer *fb, int length, int width, int x, int y, pixel color );
void drawRectFill( frameBuffer * fb, int x, int y, int width, int height, pixel color );

void drawTriangleFrame( frameBuffer *fb, int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2, int cx1,  int cy1, int cx2, int cy2, pixel color );
void drawTriangleFill( frameBuffer *fb, int x1, int y1, int x2, int y2, int x3, int y3, pixel color );

void drawCircleFrame( frameBuffer *fb, int x0, int y0, int radius, pixel color );
void drawEllipseFrame( frameBuffer * fb, int xc, int yc, int width, int height, pixel color );

void bezier( frameBuffer *fb, int x1, int y1, int x2, int y2, int x3, int y3, pixel color );

//void polygonFill( frameBuffer *fb, float *vertices, int numOfVerts, int yMax, pixel color);

void bitBlt(frameBuffer *dst, int dstx, int dsty, frameBuffer *src, int srcx, int srcy, int srcWidth, int srcHeight );

void drawText(frameBuffer *fb, int px, int py, char text[], pixel color);
