--scene.lua
local ffi = require("ffi")
local draw = require("render_ffi")
local colors = require("colors")
local ppm = require("ppm")
local lbl = require("label")
local boundingbox = require("boundingbox")

-- Create framebuffer
-- TODO: extract this to its own file

local width = 340;
local height = 100;
local x = 0;
local y = 0;
local data = nil;
local ownsData = 1;
local pixelStride = 0;

local fb = draw.createFrameBuffer ( width, height, x, y, data, ownsData, pixelStride );
assert(fb ~= nil)

bbox = boundingbox:new(50, 50, 2, 2, colors.PINK, {
  lbl:new(5,5,"hello",colors.PINK)
})
bbox:draw(fb)

ppm.write_PPM_binary("hellolabel.ppm", fb.data, fb.width, fb.height, 3*width)
