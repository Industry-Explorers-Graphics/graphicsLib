--boundingbox.lua
local ffi = require("ffi")
local drawLib = require("render_ffi")

local BoundingBox = {}
local BoundingBox_mt = {
  __index = BoundingBox;
}

function BoundingBox.new(self, length, width, x, y, color, children)
  local obj = {
    length = length;
    width = width;
    x = x;
    y = y;
    color = color;
    children = children;
  }
  setmetatable(obj, BoundingBox_mt)
  return obj
end

function BoundingBox.draw(self, fb)
  drawLib.drawRectFrame(fb, self.length, self.width, self.x, self.y, self.color) 
  if self.children ~= nil then 
    for _,child in ipairs(self.children) do
      child:draw(fb)
    end
  end
end

return BoundingBox  
