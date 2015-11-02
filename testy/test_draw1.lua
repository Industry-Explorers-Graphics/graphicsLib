--test_draw1.lua
local ffi = require("ffi")
local draw = require("render_ffi")
local colors = require("colors")
local ppm = require("ppm")



-- Create a framebuffer
local width = 320;
local height = 256;
local x = 0;
local y = 0;
local data = nil;
local ownsData = 1;
local pixelStride = 0;

local fb = draw.createFrameBuffer ( width, height, x, y, data, ownsData, pixelStride );
assert(fb ~= nil)

-- draw some lines in it
local color = ffi.new("pixel", 255, 0, 0);

draw.drawHorizontalLine( fb, width-1, 0, 10, color );
draw.drawHorizontalLine( fb, width-1, 0, height-10, color );

draw.drawVerticalLine( fb, height-1, 10,  0, color );
draw.drawVerticalLine( fb, height-1, width-1, 0, color );

local color = ffi.new("pixel", 0,255,0);
draw.drawDiagonalLine( fb, 0, 0, width-1, height-1, color );
draw.drawDiagonalLine( fb, width-1, 0, 0, height-1, color );

-- write it out to a ppm file
ppm.write_PPM_binary("is_a_test.ppm", fb.data, fb.width, fb.height, 3*width)


-- The End
