--slider.lua
local drawLib = require("render_ffi")
local colors = require("colors")

local Handle = {}
local Handle_mt = {
  __index = Handle;
}

local Bar = {}
local Bar_mt = {
  __index = Bar;
}

local Slider = {}
local Slider_mt = {
  __index = Slider;
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

function Slider.new(self, x, y, width, height, color, state)
  local obj = {
    x = x;
    y = y;
    width = width;
    height = height;
    color = color;
    state = state;
  }
  setmetatable(obj, Slider_mt)
  return obj
end 

function Slider.draw(self, fb)
  if self.state == 0 then
    local bar = Bar:new(self.x, 0.5 * self.height, self.width, 0.5 * self.height, colors.BLUE)
    local handle = Handle:new(self.x, 0.5 * self.height, 0.5 * self.height, colors.YELLOW)
    bar:draw(fb)
    handle:draw(fb)
  end
  if state == 1 then
    print("error: no io library in place")
  end
end

return Slider
