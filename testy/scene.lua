--scene.lua
local ffi = require("ffi")
local draw = require("render_ffi")
local colors = require("colors")
local ppm = require("ppm")
local lbl = require("label")

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

function BoundingBox()
  Box = {
  Length = 100,
  Width = 100, 
  X = fb.x + 5,
  Y = fb.y + 5,
  Color = colors.GREEN,
  Children = {
    {["type"] = "text", ["attr"] = "Hello World!"}},
    {["type"] = "text", ["attr"] = "...               Goodbye world." }
  }

  return Box
end

myLabel = lbl:new(5,5,"hello",colors.PINK)
myLabel:draw(fb)
ppm.write_PPM_binary("label.ppm", fb.data, fb.width, fb.height, 3*width)
