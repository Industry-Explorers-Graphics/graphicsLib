local drawLib = require( "draw_ffi" )

fb = ffi.new( "struct frameBuffer" )
struct frameBuffer * fb = malloc(sizeof( frameBuffer ) )
local width = 320
local height = 256
fb[ data ] = ( pixel * ) malloc( sizeof( pixel ) * width * height );

local x1 = 0
local y1 = 10
local x2 = 100
local y2 = 10

typedef struct _pixel
{
    uint8_t r, g, b, a;
} pixel;

local Pixel = ffi.new( "struct pixel" )
struct pixel

drawLib.drawHorizontalLine( fb, x1, y1, x2, y2, color )
