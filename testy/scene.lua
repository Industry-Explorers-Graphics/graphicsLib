--scene.lua
local ffi = require("ffi")
local draw = require("render_ffi")
local lbl = require("label")
local colors = require("colors")
local ppm = require("ppm")
local boundingbox = require("boundingbox")

local width = 340;
local height = 100;
local x = 0;
local y = 0;
local data = nil;
local pixelStride = 0;

local fb = draw.createFrameBuffer ( width, height, x, y, data, pixelStride );
assert(fb ~= nil)

bbox = boundingbox:new(50, 50, 2, 2, colors.PINK, {
  lbl:new(5,5,"hello",colors.PINK)
})
bbox:draw(fb)

ppm.write_PPM_binary("hellolabel.ppm", fb.data, fb.width, fb.height, 4*width)
