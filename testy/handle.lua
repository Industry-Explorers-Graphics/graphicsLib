--handle.lua
local drawLib = require("render_ffi")
local colors = require("colors")

local Handle = {}
local Handle_mt = {
  __index = Handle;
}

function Handle.new(self, x, y, radius, color)
  local obj = {
    x = x;
    y = y;
    radius = radius;
    color = color;
  }
  setmetatable(obj, Handle_mt)
  return obj
end

function Handle.draw(self, fb)
  drawLib.drawCircleFill(fb , self.x, self.y, self.radius, self.color);
end

return Handle
