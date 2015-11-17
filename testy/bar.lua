--bar.lua
local drawLib = require("render_ffi")
local colors = require("colors")

local Bar = {}
local Bar_mt = {
  __index = Bar;
}

function Bar.new(self, x, y, width, height, color)
  local obj = {
    x = x;
    y = y;
    width = width;
    height = height;
    color = color;
  }
  setmetatable(obj, Bar_mt)
  return obj
end

function Bar.draw(self, fb)
  drawLib.drawRectFill(fb, self.x, self.y, self.width, self.height, self.color);
end


-- check if point is within the bar
function Bar.contains(self, x, y)
  if x >= self.x and x <= self.x + self.width and y >= (0.5 + self.height) and y <= self.y + self.height then
    return true
  else
    return false
  end
end

return Bar
