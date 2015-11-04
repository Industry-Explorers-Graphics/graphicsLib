local ffi = require( "ffi" )
local drawLib = require( "render_ffi" )
local lbl = require( "label" )
local colors = require( "colors" )
local ppm = require( "ppm" )

--create the framebuffer
local width = 300;
local height = 100;
local x = 0;
local y = 0;
local data = nil;
local pixelStride = 0;

local fb = drawLib.createFrameBuffer( width, height, x, y, data, pixelStride )
assert( fb ~= nil )

--why doesn't myLabel have 'local' in front?
--print a text label
myLabel = lbl:new( 1, 1, "Bienvenida!", colors.PINK )
myLabel:draw( fb )

--write it out to a ppm file
ppm.write_PPM_binary( "testText.ppm", fb.data, fb.width, fb.height, 4*width )
