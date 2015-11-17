--drawSlider.lua
local ffi = require( "ffi" )
local drawLib = require( "render_ffi" )
local lbl = require( "label" )
local colors = require( "colors" )
local ppm = require( "ppm" )
local boundingbox = require("boundingbox")
local radiobutton = require("radiobutton")
local slider = require("slider")
local bar = require("bar")
local handle = require("handle")


--create the framebuffer
local width = 340;
local height = 100;
local x = 0;
local y = 0;
local data = nil;
local pixelStride = 0;

local fb = drawLib.createFrameBuffer( width, height, x, y, data, pixelStride )
assert( fb ~= nil )

local bar = bar:new(self.x, 0.5 * self.height, self.width, 0.5 * self.height, colors.BLUE)
local handle = bandle:new(self.x + (0.5 * self.height), self.y + (0.25 * self.height), 0.5 * self.height, colors.YELLOW)


bbox = boundingbox:new(50, 50, 2, 2, colors.PINK, {
    slider:new(bar, handle, 0, 10, 0)
})
bbox:draw(fb)

ppm.write_PPM_binary( "slider.ppm", fb.data, fb.width, fb.height, 4*width )
