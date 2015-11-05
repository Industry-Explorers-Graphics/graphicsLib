--drawRadioButton.lua
local ffi = require( "ffi" )
local drawLib = require( "render_ffi" )
local lbl = require( "label" )
local colors = require( "colors" )
local ppm = require( "ppm" )
local boundingbox = require("boundingbox")
local radiobutton = require("radiobutton")

--create the framebuffer
local width = 340;
local height = 100;
local x = 0;
local y = 0;
local data = nil;
local pixelStride = 0;

local fb = drawLib.createFrameBuffer( width, height, x, y, data, pixelStride )
assert( fb ~= nil )

--why doesn't myLabel have 'local' in front?
--print a text label
bbox = boundingbox:new(50, 50, 2, 2, colors.PINK, {
    lbl:new(5, 5, "B", colors.PINK),
    radiobutton:new(10, 5, colors.CLEAR, 1)
})
bbox:draw(fb)

drawLib.drawHorizontalLine(fb, 50, 10, 20, colors.GREEN)
drawLib.drawHorizontalLine(fb, 70, 10, 35, colors.GREEN_T)
--drawLib.drawHorizontalLine(fb, 70, 10, 50, colors.BLUE)


--write it out to a ppm file
ppm.write_PPM_binary( "newTests.ppm", fb.data, fb.width, fb.height, 4*width )
