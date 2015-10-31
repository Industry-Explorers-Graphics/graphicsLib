--scene.lua
local ffi = require("ffi")
local draw = require("render_ffi")
local colors = require("colors")
local ppm = require("ppm")

-- Create framebuffer
-- TODO: extract this to it's own file

local width = 320;
local height = 256;
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
  Width = 110, 
  X = 100,
  Y = 100,
  Color = colors.PINK,
  Children = {},
  }
  return Box
  --self.Length = params.Length or 1;
  --self.Width = params.Width or 1;
  --self.X = params.X or 100;
  --self.Y = params.Y or 200;
  --self.Color = params.color or PINK;
  --self.Children = params.Children or {};
  
  --self:super(params)
    
end

local bbox = BoundingBox()
draw.drawRectFrame(fb, bbox.Length, bbox.Width, bbox.X, bbox.Y, bbox.Color);
--for _,child in ipairs(children) do
--  draw.Text(child.attributes)
print(ffi)
ppm.write_PPM_binary("bbox.ppm", fb.data, fb.width, fb.height, 3*width)
