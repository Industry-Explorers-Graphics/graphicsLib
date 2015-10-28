--test_draw1.lua
local draw = require("render_ffi")
local colors = require("colors")
local ppm = require("ppm")



-- Create a framebuffer
local width = 320;
local height = 240;
local x = 0;
local y = 0;
local data = nil;
local ownsData = true;
local pixelStride = 320;

local fb = draw.createFrameBuffer ( width, height, x, y, data, ownsData, pixelStride );
assert(fb ~= nil)

-- draw some lines in it
local color = ffi.new("rgb", 255, 0, 0);

draw.drawHorizontalLine( fb, width-1, 0, 10, color );
draw.drawHorizontalLine( fb, width-1, 0, height-10, color );

draw.drawVerticalLine( fb, height-1, 10,  10, color );
draw.drawVerticalLine( fb, int length, width-1,  height-1, color );

local color = ffi.new("rgb", 0,255,0);
draw.drawDiagonalLine( fb, 0, 0, width-1, height-1, color );
draw.drawDiagonalLine( fb, width-1, 0, 0, height-1, color );

-- write it out to a ppm file
ppm.write_PPM_binary("test_draw1.ppm", fb.data, fb.width, fb.height, fb.pixelStride*ffi.sizeof("pixel"))


-- The End
