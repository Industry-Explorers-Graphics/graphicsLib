local ffi = require( "ffi" )
local drawLib = require( "render_ffi" )
local lbl = require( "label" )
local colors = require( "colors" )
local ppm = require( "ppm" )

--create the framebuffer
local width = 340;
local height = 100;
local x = 0;
local y = 0;
local data = nil;
local ownsData = 1;
local pixelStride = 0;

local fb = drawLib.createFrameBuffer( width, height, x, y, data, ownsData, pixelStride )
assert( fb ~= nil )

--why doesn't myLabel have 'local' in front?
--print a text label
myLabel = lbl.Label:new( 30, 60, "Bienvenida mi amiga!", colors.RED )
myLabel:draw( fb )

--write it out to a ppm file
ppm.write_PPM_binary( "testText.ppm", fb.data, fb.width, fb.height, 3*width )
