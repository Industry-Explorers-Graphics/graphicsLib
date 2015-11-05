--drawLabel.lua
local ffi = require( "ffi" )
local drawLib = require( "render_ffi" )
local lbl = require( "label" )
local colors = require( "colors" )
local ppm = require( "ppm" )
local boundingbox = require("boundingbox")

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
    lbl:new( 5, 5, "B", colors.PINK )
})
bbox:draw(fb)

--write it out to a ppm file
ppm.write_PPM_binary( "testText.ppm", fb.data, fb.width, fb.height, 4*width )
